/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __HARDDRIVE_H__
#define __HARDDRIVE_H__

#include <vector>
#include <string>
#include <map>
#include "info.h"

class HardDrive : public Info
{
    public:
        struct Partition
        {
            Partition() {
                Size = 0;
                Avail = 0;
                Mounted = false;
            }
            std::string Name;
            std::string MountPoint;
            double Size;
            double Avail;
            std::string SizeUnit;
            std::string AvailUnit;
            std::string FileSystem;
            bool Mounted;
        };
        struct DiskDevice {
            std::string Name;
            double Size;
            std::string SizeUnit;
            std::map<std::string, Partition> Partitions;
        };

        HardDrive();
        ~HardDrive();
        std::string output();

        friend std::ostream& operator<<(std::ostream& stream, HardDrive& hd);

    protected:
        std::map<std::string, DiskDevice> mDevices;
        int mPartitionCount;

        void addPartitionInfo();

};

#endif	// __HARDDRIVE_H__

