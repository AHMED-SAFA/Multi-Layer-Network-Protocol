#ifndef ARPTABLE_H_
#define ARPTABLE_H_
#include <omnetpp.h>
using namespace omnetpp;

#include <map>
#include <string>

class ARPTable {
private:
    std::map<std::string, std::string> ipToMac; // IP -> MAC

public:
    void addEntry(const std::string& ip, const std::string& mac);
    std::string getMAC(const std::string& ip);
    bool hasEntry(const std::string& ip);
};

#endif
