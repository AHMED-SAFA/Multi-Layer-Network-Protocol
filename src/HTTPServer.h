#ifndef HTTPSERVER_H_
#define HTTPSERVER_H_

#include <omnetpp.h>
#include "ARPTable.h"
#include <omnetpp.h>
using namespace omnetpp;

class HTTPServer : public cSimpleModule
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
