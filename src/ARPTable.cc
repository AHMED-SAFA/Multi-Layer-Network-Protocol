// src/ARPTable.cc
#include "ARPTable.h"
#include <omnetpp.h>
using namespace omnetpp;
#include <iostream>

void ARPTable::addEntry(const std::string& ip, const std::string& mac) {
    ipToMac[ip] = mac;
}

std::string ARPTable::getMAC(const std::string& ip) {
    auto it = ipToMac.find(ip);
    if (it != ipToMac.end()) {
        return it->second;
    }
    return "";
}

bool ARPTable::hasEntry(const std::string& ip) {
    return ipToMac.find(ip) != ipToMac.end();
}
