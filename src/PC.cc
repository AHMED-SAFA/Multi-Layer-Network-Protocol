// src/PC.cc
#include "PC.h"
#include "messages/ARPPacket_m.h"
#include "messages/ICMPPacket_m.h"
#include "messages/DNSPacket_m.h"
#include <string>
#include <cstring>

using namespace omnetpp;

Define_Module(PC);

void PC::initialize()
{
    ipAddr = par("ipAddr").stdstringValue();
    macAddr = par("macAddr").stdstringValue();

    pingTimer = new cMessage("PingTimer");
    dnsTimer = new cMessage("DNSTimer");

    scheduleAt(0.5, pingTimer);
    scheduleAt(1.0, dnsTimer);
}

void PC::handleMessage(cMessage *msg)
{
    if (msg == pingTimer) {
        std::string target = dnsResolved ? resolvedIP : dnsServerIP;
        sendPingTo(target);
        scheduleAt(simTime() + 1.0, pingTimer);
    }
    else if (msg == dnsTimer) {
        if (!dnsResolved) {
            sendDNSQuery();
        }
    }
    else if (ARPPacket *arp = dynamic_cast<ARPPacket*>(msg)) {
        if (!arp->isRequest() && std::string(arp->getDstIP()) == ipAddr) {
            EV << "PC: Learned MAC for " << arp->getSrcIP() << " = " << arp->getSrcMAC() << "\n";
            arpTable.addEntry(std::string(arp->getSrcIP()), std::string(arp->getSrcMAC()));
        }
        delete msg;
    }
    else if (ICMPPacket *icmp = dynamic_cast<ICMPPacket*>(msg)) {
        if (!icmp->isEchoRequest()) {
            EV << "PC: Received ping reply from " << icmp->getSrcIP() << " (seq=" << icmp->getSeqNum() << ")\n";
        }
        delete msg;
    }
    else if (DNSPacket *dns = dynamic_cast<DNSPacket*>(msg)) {
        if (!dns->isQuery()) {
            resolvedIP = std::string(dns->getAnswerIP());
            dnsResolved = true;
            EV << "PC: DNS resolved " << httpServerName << " -> " << resolvedIP << "\n";
            EV << "PC: Fetching web content from " << resolvedIP << "\n";
        }
        delete msg;
    }
}

// ✅ IMPLEMENT sendPingTo with proper .c_str()
void PC::sendPingTo(const std::string& targetIP)
{
    if (!arpTable.hasEntry(targetIP)) {
        EV << "PC: No ARP entry for " << targetIP << ", sending ARP request\n";
        sendARPRequest(targetIP);
        return;
    }

    ICMPPacket *icmp = new ICMPPacket("ICMP-Request");
    icmp->setSrcIP(ipAddr.c_str());      // ✅
    icmp->setDstIP(targetIP.c_str());    // ✅
    icmp->setSeqNum(++pingSeq);
    icmp->setIsEchoRequest(true);
    send(icmp, "out");
}

void PC::sendARPRequest(const std::string& targetIP)
{
    ARPPacket *arp = new ARPPacket("ARP-Request");
    arp->setSrcIP(ipAddr.c_str());       // ✅
    arp->setSrcMAC(macAddr.c_str());     // ✅
    arp->setDstIP(targetIP.c_str());     // ✅
    arp->setDstMAC("FF:FF:FF:FF:FF:FF");
    arp->setIsRequest(true);
    send(arp, "out");
}

void PC::sendDNSQuery()
{
    if (!arpTable.hasEntry(dnsServerIP)) {
        sendARPRequest(dnsServerIP);
        scheduleAt(simTime() + 0.2, dnsTimer);
        return;
    }

    DNSPacket *dns = new DNSPacket("DNS-Query");
    dns->setIsQuery(true);
    dns->setQueryName(httpServerName.c_str());  // ✅
    send(dns, "out");
}
