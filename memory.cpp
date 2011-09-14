
#include <stdio.h>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include "memory.h"
#include "dmiparser.h"
#include "util.h"


Memory::Memory()
{
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
