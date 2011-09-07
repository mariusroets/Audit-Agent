
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
    read();
}
HardDrive::~HardDrive()
{
}
std::string HardDrive::output()
{
    stringstream stream;
    typedef std::map<std::string, HardDrive::DiskDevice>::iterator map_iterator;
    stream << "Hard Drives Count=" << mPartitionCount << mLineEnding;
    map_iterator j = mDevices.begin();
    while (j != mDevices.end()) {
        std::map<std::string, HardDrive::Partition> partitions;
        partitions = j->second.Partitions;
        std::map<std::string, HardDrive::Partition>::iterator k = partitions.begin();
        int count = 1;
        while (k != partitions.end()) {
            if (k->second.Mounted) {
                stream << "HDLetter" << count << "=" << k->second.Name << mLineEnding;
                stream << "HDSpace" << count << "=" << k->second.Size << mLineEnding;
                stream << "HDFree" << count << "=" << k->second.Avail << mLineEnding;
                stream << "HDSerial" << count << "=" << mLineEnding;
                stream << "HDFileSystem" << count << "=" << k->second.FileSystem << mLineEnding;
                stream << "HDLabel" << count << "=" << k->second.MountPoint << mLineEnding;
                count++;
            }
            ++k;
        }

        ++j;
    }
    return stream.str();
}
void HardDrive::read()
{
    typedef std::map<std::string, DiskDevice>::iterator map_iterator;

    CommandParser parser;
    std::vector<std::string> lines = parser.parse("sudo /sbin/fdisk -l");
    std::vector<std::vector<std::string> > fields = parser.split(SPACES);
    // Process the lines one by one
    for (unsigned int i = 0; i < lines.size() ; ++i) {
        // Assume that lines starting with '/' contains partition information
        if (lines[i][0] == '/') {
            std::string dev = fields[i][0].substr(0,8);
            if (mDevices.find(dev) == mDevices.end()) {
                DiskDevice d;
                d.Name = dev;
                mDevices[dev] = d;
            }
            Partition p;
            p.Name = fields[i][0];
            mDevices[dev].Partitions.insert(std::pair<std::string, Partition>(p.Name, p));
        }
    }
    addPartitionInfo();
    // For debugging
/*     map_iterator j = mDevices.begin();
    while (j != mDevices.end()) {
        Util::debugMsg(j->first);
        std::map<std::string, Partition> partitions;
        partitions = j->second.Partitions;
        std::map<std::string, Partition>::iterator k = partitions.begin();
        while (k != partitions.end()) {
            Util::debugMsg("   " + k->second.Name);
            if (k->second.Mounted) {
                std::cerr << "   " << k->second.Size << k->second.SizeUnit << std::endl;
                std::cerr << "   " << k->second.Avail << k->second.AvailUnit << std::endl;
            }
            ++k;
        }

        ++j;
    }  */
}
void HardDrive::addPartitionInfo()
{
    mPartitionCount = 0;
    CommandParser parser;
    std::vector<std::string> lines = parser.parse("sudo df -hTP");
    std::vector<std::vector<std::string> > fields = parser.split(SPACES);

    typedef std::map<std::string, DiskDevice>::iterator map_iterator;

    // Process the lines one by one
    for (unsigned int i = 0; i < lines.size() ; ++i) {
        if (lines[i][0] != '/')
            continue;
        Partition p;
        // /dev/sda1     ext4     40G   12G   26G  32% /
        std::string dev = fields[i][0].substr(0,8);
        p.Name = fields[i][0];
        p.Size = atof(fields[i][2].substr(0,fields[i][2].size()-1).c_str());
        p.SizeUnit = fields[i][2].substr(fields[i][2].size()-1);
        p.Avail = atof(fields[i][4].substr(0,fields[i][4].size()-1).c_str());
        p.AvailUnit = fields[i][4].substr(fields[i][4].size()-1);
        p.FileSystem = fields[i][1];
        p.MountPoint = fields[i][6];
        p.Mounted = true;
        mPartitionCount++;
        mDevices[dev].Partitions[p.Name] = p;
    }
}
std::ostream& operator<<(std::ostream& stream, HardDrive& hd)
{
    stream << hd.output();
    return stream;
}
