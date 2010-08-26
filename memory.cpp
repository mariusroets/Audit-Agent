
#include <vector>
#include <boost/algorithm/string.hpp>
#include "memory.h"
#include "util.h"


Memory::Memory()
{
    read();
}
void Memory::read()
{
    mSlots = 0;
    mSlotsUsed = 0;
    bool skip = false;
    std::string s = Util::exec("sudo dmidecode/dmidecode --type 17");
    std::vector<std::string> lines;
    boost::split(lines, s, boost::is_any_of("\n\r"), boost::token_compress_on);
    for (unsigned int i = 0; i < lines.size() ; ++i) {
        boost::trim(lines[i]);
        if (lines[i].empty())
            continue;
        if (lines[i] == "Memory Device") {
            mSlots++;
            skip = false;
        }
        if (skip)
            continue;
        std::vector<std::string> fields;
        boost::split(fields, lines[i], boost::is_any_of(":"));
        if (fields.size() < 2)
            continue;
        boost::trim(fields[0]);
        boost::trim(fields[1]);
        if (fields[0] == "Size") {
            if (fields[1] != "No Module Installed") {
                mSlotsUsed++;
            } else {
                skip = true;
            }
        } else if (fields[0] == "Speed") {
            mSpeed = fields[1];
        } else if (fields[0] == "Type") {
            mType = fields[1];
        }

    }
}

std::ostream& operator<<(std::ostream& stream, Memory& mem)
{
    stream << "Memory=" << 4096 << std::endl;
    stream << "Memory Slots Used=" << mem.mSlotsUsed << std::endl;
    stream << "Memory Slots Free=" << mem.mSlots-mem.mSlotsUsed << std::endl;
    stream << "Memory Max Size=" << 4096 << std::endl;
    stream << "Memory Types=" << mem.mType << std::endl;
    stream << "Memory Speeds=" << mem.mSpeed << std::endl;
    stream << "Memory Voltages=" << mem.mVoltage << std::endl;
    return stream;
}
