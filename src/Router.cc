// Router.cc
#include <omnetpp.h>
#include "messages/ARPPacket_m.h"
#include "messages/ICMPPacket_m.h"
#include "messages/DNSPacket_m.h"

using namespace omnetpp;

class Router : public cSimpleModule
{
  protected:
    virtual void handleMessage(cMessage *msg) override;
};

Define_Module(Router);

void Router::handleMessage(cMessage *msg)
{
    if (msg->arrivedOn("inPC")) {
        if (dynamic_cast<ARPPacket*>(msg)) {
            ARPPacket *arp = check_and_cast<ARPPacket*>(msg);
            if (arp->isRequest()) { // optional check
                send(msg->dup(), "outDNS");
                send(msg->dup(), "outHTTP");
            }
            send(msg, "outPC");
        }
        else if (dynamic_cast<DNSPacket*>(msg)) {
            send(msg, "outDNS");
        } else {
            send(msg, "outHTTP");
        }
    }
    else if (msg->arrivedOn("inDNS")) {
        send(msg, "outPC");
    }
    else if (msg->arrivedOn("inHTTP")) {
        send(msg, "outPC");
    }
}
