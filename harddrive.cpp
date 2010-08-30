
#include <boost/algorithm/string.hpp>
#include "harddrive.h"
#include "commandparser.h"
#include "util.h"

HardDrive::HardDrive()
{
    read();
}
HardDrive::~HardDrive()
{
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
    std::vector<std::string> lines = parser.parse("sudo df -h");
    std::vector<std::vector<std::string> > fields = parser.split(SPACES);

    typedef std::map<std::string, DiskDevice>::iterator map_iterator;

    // Process the lines one by one
    for (unsigned int i = 0; i < lines.size() ; ++i) {
        if (lines[i][0] != '/')
            continue;
        Partition p;
        std::string dev = fields[i][0].substr(0,8);
        p.Name = fields[i][0];
        p.Size = atof(fields[i][1].substr(0,fields[i][1].size()-1).c_str());
        p.SizeUnit = fields[i][1].substr(fields[i][1].size()-1);
        p.Avail = atof(fields[i][3].substr(0,fields[i][3].size()-1).c_str());
        p.AvailUnit = fields[i][3].substr(fields[i][3].size()-1);
        p.Mounted = true;
        mPartitionCount++;
        mDevices[dev].Partitions[p.Name] = p;
    }
}
std::ostream& operator<<(std::ostream& stream, HardDrive& hd)
{
    typedef std::map<std::string, HardDrive::DiskDevice>::iterator map_iterator;
    stream << "Hard Drives Count=" << hd.mPartitionCount << std::endl;
    map_iterator j = hd.mDevices.begin();
    while (j != hd.mDevices.end()) {
        std::map<std::string, HardDrive::Partition> partitions;
        partitions = j->second.Partitions;
        std::map<std::string, HardDrive::Partition>::iterator k = partitions.begin();
        int count = 1;
        while (k != partitions.end()) {
            if (k->second.Mounted) {
                stream << "HDLetter" << count << "=" << k->second.Name << std::endl;
                stream << "HDSpace" << count << "=" << k->second.Size << std::endl;
                stream << "HDFree" << count << "=" << k->second.Avail << std::endl;
                stream << "HDSerial" << count << "=" << std::endl;
                stream << "HDFileSystem" << count << "=" << std::endl;
                stream << "HDLabel" << count << "=" << std::endl;
                count++;
            }
            ++k;
        }

        ++j;
    }
    return stream;
}
