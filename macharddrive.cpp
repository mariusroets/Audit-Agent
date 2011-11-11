
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
    mDevices.clear();
    vector<string> device_list = SYS->children("Serial-ATA:Serial-ATA Bus");
    for (int i = 0; i < (int)device_list.size(); i++) {
        // Get the physical drives
        string key_base = string("Serial-ATA:Serial-ATA Bus") + device_list[i] + ":"; 
        mDevices.push_back(DiskDevice());
        string key = key_base + "Model";
        mDevices[i].Name = SYS->value(key);
        mDevices[i].Model = mDevices[i].Name;
        key = key_base + "Serial Number";
        mDevices[i].Serial = SYS->value(key);
        key = key_base + "Revision";
        mDevices[i].Revision = SYS->value(key);
        key = key_base + "Capacity";
        mDevices[i].Capacity = Size(SYS->value(key));
        // Get the partitions
        key = key_base + "Volumes";
        vector<string> partition_list = SYS->children(key); 
        for (int j = 0; j < (int)partition_list.size(); j++) {
            mDevices[i].Partitions.push_back(Partition());
            mDevices[i].Partitions[j].Name = partition_list[j];
            key_base = key_base + partition_list[j] + ":";
            key = key_base + "Capacity";
            mDevices[i].Partitions[j].Capacity = Size(SYS->value(key));
            key = key_base + "Available";
            mDevices[i].Partitions[j].Avail = Size(SYS->value(key));
            key = key_base + "File System";
            mDevices[i].Partitions[j].FileSystem = SYS->value(key);
            key = key_base + "Mount Point";
            mDevices[i].Partitions[j].MountPoint = SYS->value(key);
            mDevices[i].Partitions[j].Mounted = true;
        }

        
    }

}
