
#include <vector>
#include <cstdlib>
#include "network.h"
#include "dmiparser.h"
#include "commandparser.h"
#include "util.h"
#include "architecture.h"
#include "linuxnetwork.h"
#include "macnetwork.h"

Network::Network()
{
}

Network::~Network()
{
}

std::string Network::output()
{
    stringstream stream;
    stream << mHardware << endl;
    stream << "Adapters Count=" << mAdapters.size() << endl;
    vector<string> mac_addresses;
    vector<string> ip_addresses;
    vector<string> subnet_addresses;
    for (int i = 0 ; i < (int)mAdapters.size(); i++) {
        stream << "Adapters" << i+1 << "=" << mAdapters[i].name << endl;
        stream << "Adapters Mac" << i+1 << "=" << mAdapters[i].mac << endl;
        stream << "Adapters IP" << i+1 << "=" << mAdapters[i].ip << endl;
        stream << "Adapters Cnt" << i+1 << "=" << mAdapters[i].count << endl;
        stream << "Adapters Suffix" << i+1 << "=" << mAdapters[i].suffix << endl;
        stream << "Adapters Subnet" << i+1 << "=" << mAdapters[i].mask << endl;
        if (!mAdapters[i].ip.empty())
            ip_addresses.push_back(mAdapters[i].ip);
        if (!mAdapters[i].mac.empty())
            mac_addresses.push_back(mAdapters[i].mac);
        if (!mAdapters[i].mask.empty())
            subnet_addresses.push_back(mAdapters[i].mask);
        
    }
    // Some redundant repepitions of the given file format
    stream << "IP Address Count=" << ip_addresses.size() << endl;
    for (int i = 0; i < (int)ip_addresses.size(); i++) {
        stream << "IP Address" << i+1 << "=" << ip_addresses[i] << endl;
    }
    stream << "MAC Address Count=" << mac_addresses.size() << endl;
    for (int i = 0; i < (int)mac_addresses.size(); i++) {
        stream << "MAC Address" << i+1 << "=" << mac_addresses[i] << endl;
    }
    stream << "Subnet Mask Count=" << subnet_addresses.size() << endl;
    for (int i = 0; i < (int)subnet_addresses.size(); i++) {
        stream << "Subnet Mask" << i+1 << "=" << subnet_addresses[i] << endl;
    }
    // Windows thingies
    stream << endl << "Winsock Version=" << endl;
    stream << "WINS Count=0" << endl;

    return stream.str();
/* 

Modems Count=1
Modems1=HDA CX11270 Soft Modem

DNS Count=0

Gateway Count=1
Gateway1=0.0.0.0
*/
}

void Network::read()
{

}

