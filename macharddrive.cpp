
#include "macharddrive.h"
#include "commandparser.h"
#include "util.h"
#include "sysprofileparser.h"
#include <boost/algorithm/string.hpp>


MacHardDrive::MacHardDrive()
{
}
MacHardDrive::~MacHardDrive()
{
}
void MacHardDrive::read()
{
    SysProfileParser *sys = SysProfileParser::Instance();
    mDevices.clear();
    vector<string> device_list = sys->children("Serial-ATA:Serial-ATA Bus");
    for (int i = 0; i < (int)device_list.size(); i++) {
        // Get the physical drives
        string key_base = string("Serial-ATA:Serial-ATA Bus:") + device_list[i] + ":"; 
        mDevices.push_back(DiskDevice());
        string key = key_base + "Model";
        mDevices[i].Name = sys->value(key);
        mDevices[i].Model = mDevices[i].Name;
        key = key_base + "Serial Number";
        mDevices[i].Serial = sys->value(key);
        key = key_base + "Revision";
        mDevices[i].Revision = sys->value(key);
        key = key_base + "Capacity";
        mDevices[i].Capacity = Size(sys->value(key));
        // Get the partitions
        key = key_base + "Volumes";
        vector<string> partition_list = sys->children(key); 
        for (int j = 0; j < (int)partition_list.size(); j++) {
            string key_base2 = key_base + "Volumes:" + partition_list[j] + ":";
            mDevices[i].Partitions.push_back(Partition());
            mDevices[i].Partitions[j].Name = partition_list[j];
            key = key_base2 + "Capacity";
            mDevices[i].Partitions[j].Capacity = Size(sys->value(key));
            key = key_base2 + "Available";
            mDevices[i].Partitions[j].Avail = Size(sys->value(key));
            key = key_base2 + "File System";
            mDevices[i].Partitions[j].FileSystem = sys->value(key);
            key = key_base2 + "Mount Point";
            mDevices[i].Partitions[j].MountPoint = sys->value(key);
            mDevices[i].Partitions[j].Mounted = true;
        }

        
    }

}
