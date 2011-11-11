#include "macnetwork.h"
#include "sysprofileparser.h"

MacNetwork::MacNetwork()
{
    read();
}
MacNetwork::~MacNetwork()
{
}
void MacNetwork::read()
{
    mAdapters.clear();
    vector<string> adapters = SYS->children("Network");

    for (int i = 0; i < (int)adapters.size(); i++) {
        mAdapters.push_back(Adapter());
        string key_base = string("Network:") + adapters[i] + ":";
        string key = key_base + "BSD Device Name";
        mAdapters[i].name = SYS->value(key);
        key = key_base + "IPv4:Addresses";
        mAdapters[i].ip = SYS->value(key);
        key = key_base + "IPv4:Subnet Masks";
        mAdapters[i].mask = SYS->value(key);
        key = key_base + "Ethernet:MAC Address";
        mAdapters[i].mac = SYS->value(key);
        mAdapters[i].suffix = "";
        mAdapters[i].count = 1;
    }

}

