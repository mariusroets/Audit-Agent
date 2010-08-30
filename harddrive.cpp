
#include <boost/algorithm/string.hpp>
#include "harddrive.h"
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
    std::string s = Util::exec("sudo /sbin/fdisk -l");
    typedef std::map<std::string, DiskDevice>::iterator map_iterator;

    // Split output in vector of lines
    std::vector<std::string> lines;
    boost::split(lines, s, boost::is_any_of("\n\r"), boost::token_compress_on);
    // Process the lines one by one
    for (unsigned int i = 0; i < lines.size() ; ++i) {
        boost::trim(lines[i]);
        // Skip empty lines
        if (lines[i].empty())
            continue;
        std::vector<std::string> fields;
        boost::split(fields, lines[i], boost::is_any_of(SPACES), boost::token_compress_on);
        // Assume that lines starting with '/' contains partition information
        if (fields[0][0] == '/') {
            std::string dev = fields[0].substr(0,8);
            map_iterator i = mDevices.find(dev);
            if (i == mDevices.end()) {
                DiskDevice d;
                d.Name = dev;
                mDevices[dev] = d;
            }
            Partition p;
            p.Name = fields[0];
            mDevices[dev].Partitions.insert(std::pair<std::string, Partition>(p.Name, p));
        }
    }
    addPartitionInfo();
/*     // For debugging
    map_iterator j = mDevices.begin();
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
    } */
}
void HardDrive::addPartitionInfo()
{
    mPartitionCount = 0;
    std::string s = Util::exec("sudo df -h");
    typedef std::map<std::string, DiskDevice>::iterator map_iterator;

    // Split output in vector of lines
    std::vector<std::string> lines;
    boost::split(lines, s, boost::is_any_of("\n\r"), boost::token_compress_on);
    // Process the lines one by one
    for (unsigned int i = 0; i < lines.size() ; ++i) {
        boost::trim(lines[i]);
        // Skip empty lines
        if (lines[i].empty())
            continue;
        if (lines[i][0] != '/')
            continue;
        std::vector<std::string> fields;
        boost::split(fields, lines[i], boost::is_any_of(SPACES), boost::token_compress_on);
        Partition p;
        p.Name = fields[0];
        p.Size = atof(fields[1].substr(0,fields[1].size()-1).c_str());
        p.SizeUnit = fields[1].substr(fields[1].size()-1);
        p.Avail = atof(fields[3].substr(0,fields[3].size()-1).c_str());
        p.AvailUnit = fields[3].substr(fields[3].size()-1);
        p.Mounted = true;
        mPartitionCount++;
        map_iterator j = mDevices.begin();
        while (j != mDevices.end()) {
            std::map<std::string, Partition> partitions;
            partitions = j->second.Partitions;
            j->second.Partitions[p.Name] = p;
            ++j;
        }
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
