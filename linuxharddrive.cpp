
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
    int dIndex;
    int pIndex;
    // Process the lines one by one
    for (unsigned int i = 0; i < lines.size() ; ++i) {
        // Assume that lines starting with '/' contains partition information
        if (lines[i][0] == '/') {
            std::string dev = fields[i][0].substr(0,8);
            // Check if device exists
            dIndex = deviceIndex(dev);
            if (dIndex == -1) {
                mDevices.push_back(DiskDevice());
                dIndex = mDevices.size()-1;
                mDevices[dIndex].Name = dev;
            }
            mDevices[dIndex].Partitions.push_back(Partition());
            pIndex = mDevices[dIndex].Partitions.size()-1;
            mDevices[dIndex].Partitions[pIndex].Name = fields[i][0];
        }
    }
    addPartitionInfo();
}
void LinuxHardDrive::addPartitionInfo()
{
    CommandParser parser;
    std::vector<std::string> lines = parser.parse("sudo df -hTP");
    std::vector<std::vector<std::string> > fields = parser.split(SPACES);

    //typedef std::map<std::string, DiskDevice>::iterator map_iterator;

    int dIndex;
    int pIndex;
    // Process the lines one by one
    for (unsigned int i = 0; i < lines.size() ; ++i) {
        if (lines[i][0] != '/')
            continue;
        // /dev/sda1     ext4     40G   12G   26G  32% /
        std::string dev = fields[i][0].substr(0,8);
        dIndex = deviceIndex(dev);
        pIndex = partitionIndex(dIndex, fields[i][0]);
        mDevices[dIndex].Partitions[pIndex].Name = fields[i][0];
        mDevices[dIndex].Partitions[pIndex].Capacity = Size(fields[i][2]);
        mDevices[dIndex].Partitions[pIndex].Avail = Size(fields[i][4]);
        mDevices[dIndex].Partitions[pIndex].FileSystem = fields[i][1];
        mDevices[dIndex].Partitions[pIndex].MountPoint = fields[i][6];
        mDevices[dIndex].Partitions[pIndex].Mounted = true;
    }
}
