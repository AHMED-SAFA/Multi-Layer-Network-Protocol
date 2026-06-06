// src/PC.h
#ifndef PC_H_
#define PC_H_

#include <omnetpp.h>
#include "ARPTable.h"
#include <queue>
#include <string>  // 👈 add this

using namespace omnetpp;  // 👈 add this

class PC : public cSimpleModule
{
  private:
    std::string ipAddr;
    std::string macAddr;
    ARPTable arpTable;
    std::string dnsServerIP = "192.168.0.10";
    std::string httpServerName = "example.com";
    std::string resolvedIP = "";
    int pingSeq = 0;
    cMessage *pingTimer = nullptr;
    cMessage *dnsTimer = nullptr;
    bool dnsResolved = false;

    // 👇 ADD THIS DECLARATION
    void sendPingTo(const std::string& targetIP);

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void sendARPRequest(const std::string& targetIP);
    void sendDNSQuery();
};

#endif
