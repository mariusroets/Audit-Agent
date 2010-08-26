
#include <stdio.h>
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
    int memSize = 0;
    bool skip = false;
    // Run dmidecode and get output
    std::string s = Util::exec("sudo dmidecode/dmidecode --type 17");
    // Split output in vector of lines
    std::vector<std::string> lines;
    boost::split(lines, s, boost::is_any_of("\n\r"), boost::token_compress_on);
    // Process the lines one by one
    for (unsigned int i = 0; i < lines.size() ; ++i) {
        boost::trim(lines[i]);
        // Skip empty lines
        if (lines[i].empty())
            continue;
        //Every slot will start with a line containing "Memory Device"
        if (lines[i] == "Memory Device") {
            mSlots++;
            skip = false;
        }
        if (skip)
            continue;
        // Lines consist of name: value pairs. Split on ':' to seperate them.
        std::vector<std::string> fields;
        boost::split(fields, lines[i], boost::is_any_of(":"));
        if (fields.size() < 2)
            continue;
        boost::trim(fields[0]);
        boost::trim(fields[1]);
        if (fields[0] == "Size") {
            if (fields[1] != "No Module Installed") {
                // Memory size is a string like "1024 MB". Split it in "1024" and "MB"
                // Increment total size.
                std::vector<std::string> memFields;
                boost::split(memFields, fields[1], boost::is_any_of(" \t"), boost::token_compress_on);
                memSize += atoi(memFields[0].c_str());
                mSlotsUsed++;
                char memSizeString[50];
                sprintf(memSizeString, "%d %s", memSize, memFields[1].c_str());
                mSize = memSizeString;
            } else {
                // If there is no module installed in this slot, skip rest of the values
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
    stream << "Memory=" << mem.mSize << std::endl;
    stream << "Memory Slots Used=" << mem.mSlotsUsed << std::endl;
    stream << "Memory Slots Free=" << mem.mSlots-mem.mSlotsUsed << std::endl;
    stream << "Memory Max Size=" << mem.mSize << std::endl;
    stream << "Memory Types=" << mem.mType << std::endl;
    stream << "Memory Speeds=" << mem.mSpeed << std::endl;
    stream << "Memory Voltages=" << mem.mVoltage << std::endl;
    return stream;
}
