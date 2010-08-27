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
            std::string Name;
            std::string MountPoint;
            int Size;
            std::string SizeUnit;
        };
        struct DiskDevice {
            std::string Name;
            int Size;
            std::string SizeUnit;
            std::vector<Partition> Partitions;
        };

        HardDrive();
        ~HardDrive();

        friend std::ostream& operator<<(std::ostream& stream, HardDrive& hd);

    protected:
        void read();

    private:
        std::map<std::string, DiskDevice> mDevices;

};

#endif	// __HARDDRIVE_H__

