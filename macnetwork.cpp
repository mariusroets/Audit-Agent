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
    SysProfileParser sys;
    sys.parse();

    // Adapter 1 : Modem
    string value = sys.value("Network:Internal Modem:Type");
    if (!value.empty()) {
        mAdapters.push_back(Adapter());
        int index = mAdapters.size() - 1;
        mAdapters[index].name = sys.value("Network:Internal Modem:BSD Device Name");
        mAdapters[index].mac = "";
        mAdapters[index].ip = sys.value("Network:Internal Modem:IPv4:Addresses");
        mAdapters[index].mask = sys.value("Network:Internal Modem:IPv4:Subnet Masks");
        mAdapters[index].count = 1;
    }
    // Adapter 2 : Ethernet
    value = sys.value("Network:Ethernet:Type");
    if (!value.empty()) {
        mAdapters.push_back(Adapter());
        int index = mAdapters.size() - 1;
        mAdapters[index].name = sys.value("Network:Ethernet:BSD Device Name");
        mAdapters[index].mac = sys.value("Network:Ethernet:Ethernet:MAC Address");
        mAdapters[index].ip = sys.value("Network:Ethernet:IPv4:Addresses");
        mAdapters[index].mask = sys.value("Network:Ethernet:IPv4:Subnet Masks");
        mAdapters[index].count = 1;
    }
    // Adapter 3 : Firewire
    value = sys.value("Network:FireWire:Type");
    if (!value.empty()) {
        mAdapters.push_back(Adapter());
        int index = mAdapters.size() - 1;
        mAdapters[index].name = sys.value("Network:FireWire:BSD Device Name");
        mAdapters[index].mac = sys.value("Network:FireWire:Ethernet:MAC Address");
        mAdapters[index].ip = sys.value("Network:FireWire:IPv4:Addresses");
        mAdapters[index].mask = sys.value("Network:FireWire:IPv4:Subnet Masks");
        mAdapters[index].count = 1;
    }
}

