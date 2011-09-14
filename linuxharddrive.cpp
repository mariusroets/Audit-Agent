
#include "linuxharddrive.h"
#include "commandparser.h"
#include "util.h"

LinuxHardDrive::LinuxHardDrive()
{
    read();
}
LinuxHardDrive::~LinuxHardDrive()
{
}
void LinuxHardDrive::read()
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
