// DNSServer.h
#ifndef DNSSERVER_H_
#define DNSSERVER_H_

#include <omnetpp.h>
#include "ARPTable.h"

using namespace omnetpp;

class DNSServer : public cSimpleModule
{
  private:
    std::string ipAddr;
    std::string macAddr;
    ARPTable arpTable;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
