// DNSServer.cc
#include "DNSServer.h"
#include "messages/DNSPacket_m.h"
#include "messages/ARPPacket_m.h"
#include <string>
#include <cstring> // for strcmp

using namespace omnetpp;

Define_Module(DNSServer);

void DNSServer::initialize()
{
    ipAddr = par("ipAddr").stdstringValue();
    macAddr = par("macAddr").stdstringValue();
}

void DNSServer::handleMessage(cMessage *msg)
{
    if (ARPPacket *arp = dynamic_cast<ARPPacket*>(msg)) {
        // ✅ Use isRequest(), not getIsRequest()
        if (arp->isRequest() && std::string(arp->getDstIP()) == ipAddr) {
            EV << "DNS Server: Replying to ARP for " << ipAddr << "\n";
            ARPPacket *reply = new ARPPacket("ARP-Reply");
            reply->setSrcIP(ipAddr.c_str());     // ✅ .c_str()
            reply->setSrcMAC(macAddr.c_str());   // ✅ .c_str()
            reply->setDstIP(arp->getSrcIP());
            reply->setDstMAC(arp->getSrcMAC());
            reply->setIsRequest(false);          // ✅ setter uses setIsRequest()
            send(reply, "out");
        }
        delete msg;
    }
    else if (DNSPacket *dns = dynamic_cast<DNSPacket*>(msg)) {
        // Use isQuery(), not getIsQuery()
        if (dns->isQuery()) {
            std::string query = dns->getQueryName();
            EV << "DNS Server: Received query for " << query << "\n";
            DNSPacket *response = new DNSPacket("DNS-Response");
            response->setIsQuery(false);
            response->setQueryName(query.c_str());

            // ✅ Safe string comparison
            if (query == "example.com") {
                response->setAnswerIP("192.168.0.20");
            } else {
                response->setAnswerIP("0.0.0.0");
            }
            send(response, "out");
        }
        delete msg;
    }
}

