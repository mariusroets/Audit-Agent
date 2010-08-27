
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
            mDevices[dev].Partitions.push_back(p);
        }
    }
    // For debugging
    map_iterator j = mDevices.begin();
    while (j != mDevices.end()) {
        Util::debugMsg(j->first);
        std::vector<Partition> partitions;
        partitions = j->second.Partitions;
        std::vector<Partition>::iterator k = partitions.begin();
        while (k != partitions.end()) {
            Util::debugMsg("   " + k->Name);
            ++k;
        }

        ++j;
    }
}
std::ostream& operator<<(std::ostream& stream, HardDrive& hd)
{
    return stream;
}
