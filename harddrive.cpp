
#include "harddrive.h"

HardDrive::HardDrive()
{
    read();
}
HardDrive::~HardDrive()
{
}
void HardDrive::read()
{
    std::string s = Util::exec("sudo fdisk -l");

    // Split output in vector of lines
    std::vector<std::string> lines;
    boost::split(lines, s, boost::is_any_of("\n\r"), boost::token_compress_on);
    // Process the lines one by one
    for (unsigned int i = 0; i < lines.size() ; ++i) {
        boost::trim(lines[i]);
        // Skip empty lines
        if (lines[i].empty())
            continue;
    }
}
