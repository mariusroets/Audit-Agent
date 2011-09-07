
#include <stdio.h>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include "memory.h"
#include "dmiparser.h"
#include "util.h"


Memory::Memory()
{
    read();
}

void Memory::read()
{
    mSlotsUsed = 0;
    int memSize = 0;
    DMIParser p(DMIParser::Memory);
    p.exec();
    mSlots = p.frameCount();
    for (int i = 0; i < mSlots; ++i) {
        p.setCurrentFrame(i);
        if (p["Size"] != "No Module Installed") {
            std::vector<std::string> memFields;
            std::string size = p["Size"];
            boost::split(memFields, size, boost::is_any_of(SPACES), boost::token_compress_on);
            memSize += atoi(memFields[0].c_str());
            mSlotsUsed++;
            mSize = str(boost::format("%d %s") % memSize % memFields[1]);
            mSpeed = p["Speed"];
            mType = p["Type"];
        }
    }
}

std::string Memory::output()
{
    stringstream stream;
    stream << "Memory=" << mSize << endl;
    stream << "Memory Slots Used=" << mSlotsUsed << endl;
    stream << "Memory Slots Free=" << mSlots-mSlotsUsed << endl;
    stream << "Memory Max Size=" << mSize << endl;
    stream << "Memory Types=" << mType << endl;
    stream << "Memory Speeds=" << mSpeed << endl;
    stream << "Memory Voltages=" << mVoltage << endl;
    return stream.str();
}

std::ostream& operator<<(std::ostream& stream, Memory& mem)
{
    stream << mem.output();
    return stream;
}
