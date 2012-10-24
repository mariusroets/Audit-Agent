
#include <boost/algorithm/string.hpp>
#include "harddrive.h"
#include "commandparser.h"
#include "util.h"
/*
 * Options: hdparam
 *          hwinfo (Suse only)
 *          fdisk (not on CentOs, probably some others)
 */

HardDrive::HardDrive()
{
    mInfoType = Info::HardDrive;
}
HardDrive::~HardDrive()
{
}
std::string HardDrive::output()
{
    stringstream stream;
    stream << "Hard Drives Count=" << totalPartitions(true) << endl;
    int count = 1;
    for (int i = 0; i < (int)mDevices.size(); i++) {
        for (int j = 0; j < (int)mDevices[i].Partitions.size(); j++) {
            if (mDevices[i].Partitions[j].Mounted) {
                // Force size to be in GB regardless of what system reports
                mDevices[i].Partitions[j].Capacity.convertTo(Size::GB);
                mDevices[i].Partitions[j].Avail.convertTo(Size::GB);
                // Device is regarded as mounted if any of the partitions are mounted
                mDevices[i].Mounted = true;
                stream << "HDLetter" << count << "=" << mDevices[i].Partitions[j].Name << endl;
                stream << "HDSpace" << count << "=" << mDevices[i].Partitions[j].Capacity << endl;
                stream << "HDFree" << count << "=" << mDevices[i].Partitions[j].Avail << endl;
                stream << "HDSerial" << count << "=" << mDevices[i].Serial << endl;
                stream << "HDFileSystem" << count << "=" << mDevices[i].Partitions[j].FileSystem << endl;
                stream << "HDLabel" << count << "=" << mDevices[i].Partitions[j].MountPoint << endl;
                count++;
            }
        }
    }
    stream << endl;
    stream << "Physical Drives Count=" << mountedDrives() << endl;
    count = 0;
    for (int i = 0; i < (int)mDevices.size(); i++) {
        if (mDevices[i].Mounted) {
            count++;
            // Force size to be in GB regardless of what system reports
            mDevices[i].Capacity.convertTo(Size::GB);
            stream << "Physical Drives Device" << count << "=Device " << count << endl;
            stream << "Physical Drives Model" << count << "=" << mDevices[i].Model << endl;
            stream << "Physical Drives Serial" << count << "=" << mDevices[i].Serial << endl;
            stream << "Physical Drives Revision" << count << "=" << mDevices[i].Revision << endl;
            stream << "Physical Drives Capacity" << count << "=" << mDevices[i].Capacity << endl;
            stream << "Physical Drives Geometry" << count << "=" << mDevices[i].Geometry << endl;
        }
    }
    return stream.str();
}
bool HardDrive::exists(std::string hdname)
{
    for (int i = 0; i < (int)mDevices.size(); i++) {
        if (mDevices[i].Name == hdname)
            return true;
    }
    return false;
}
int HardDrive::deviceIndex(std::string hdname)
{
    for (int i = 0; i < (int)mDevices.size(); i++) {
        if (mDevices[i].Name == hdname)
            return i;
    }
    return -1;
}
int HardDrive::partitionIndex(std::string hdname, std::string pname)
{
    return partitionIndex(deviceIndex(hdname), pname);
}
int HardDrive::partitionIndex(int hdindex, std::string pname)
{
    for (int i = 0; i < (int)mDevices[hdindex].Partitions.size(); i++) {
        if (mDevices[hdindex].Partitions[i].Name == pname)
            return i;
    }
    return -1;

}
int HardDrive::totalPartitions(bool mounted) const
{
    int total = 0;
    for (int i = 0; i < (int)mDevices.size(); i++) {
        for (int j = 0; j < (int)mDevices[i].Partitions.size(); j++) {
            if (mounted && mDevices[i].Partitions[j].Mounted) {
                total++;
            } else if (!mounted) {
                total++;
            }
        }
    }
    return total;
}
int HardDrive::mountedDrives() const
{
    int total = 0;
    for (int i = 0; i < (int)mDevices.size(); i++) {
        if (mDevices[i].Mounted) {
            total++;
        }
    }
    return total;
}
