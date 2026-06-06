// HTTPServer.cc
#include "HTTPServer.h"
#include "messages/ICMPPacket_m.h"
#include "messages/ARPPacket_m.h"
#include <string>

using namespace omnetpp;

Define_Module(HTTPServer);

void HTTPServer::initialize()
{
    ipAddr = par("ipAddr").stdstringValue();
    macAddr = par("macAddr").stdstringValue();
}

void HTTPServer::handleMessage(cMessage *msg)
{
    if (ARPPacket *arp = dynamic_cast<ARPPacket*>(msg)) {
        if (arp->isRequest() && std::string(arp->getDstIP()) == ipAddr) {
            ARPPacket *reply = new ARPPacket("ARP-Reply");
            reply->setSrcIP(ipAddr.c_str());
            reply->setSrcMAC(macAddr.c_str());
            reply->setDstIP(arp->getSrcIP());
            reply->setDstMAC(arp->getSrcMAC());
            reply->setIsRequest(false);
            send(reply, "out");
        }
        delete msg;
    }
    else if (ICMPPacket *icmp = dynamic_cast<ICMPPacket*>(msg)) {
        if (icmp->isEchoRequest()) { // ✅ not getIsEchoRequest()
            EV << "HTTP Server: Replying to ping\n";
            ICMPPacket *reply = new ICMPPacket("ICMP-Reply");
            reply->setSrcIP(ipAddr.c_str());
            reply->setDstIP(icmp->getSrcIP());
            reply->setSeqNum(icmp->getSeqNum());
            reply->setIsEchoRequest(false);
            send(reply, "out");
        }
        delete msg;
    }
}
