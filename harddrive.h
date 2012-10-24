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
#include "size.h"
#include "info.h"


class HardDrive : public Info
{
    public:
        struct Partition
        {
            Partition() {
                Capacity = Size();
                Avail = Size();
                Mounted = false;
            }
            std::string Name;
            std::string MountPoint;
            Size Capacity;
            Size Avail;
            std::string FileSystem;
            bool Mounted;
        };
        struct DiskDevice {
            DiskDevice() {
                Name = "";
                Model = "";
                Serial = "";
                Revision = "";
                Geometry = "";
            }
            std::string Name;
            Size Capacity;
            std::string Model;
            std::string Serial;
            std::string Revision;
            std::string Geometry;
            std::vector<Partition> Partitions;
        };

        HardDrive();
        ~HardDrive();

        std::string output();
        bool exists(std::string hdname);
        int deviceIndex(std::string hdname);
        int partitionIndex(std::string hdname, std::string pname);
        int partitionIndex(int hdindex, std::string pname);
        int totalPartitions();

    protected:
        std::vector<DiskDevice> mDevices;

};

#endif	// __HARDDRIVE_H__

