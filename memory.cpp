
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
    stream << "Memory=" << mTotalSize << endl;
    stream << "Memory Slots Used=" << mSlotsUsed << endl;
    stream << "Memory Slots Free=" << mSlots-mSlotsUsed << endl;
    stream << "Memory Max Size=" << mTotalSize << endl;
    // Using values for the first non empty memory module. Typically, they should
    // be the same for all modules, but it would have been useful if the file 
    // format allowed for reporting on differences since this is a big cause of 
    // system instability.
    stream << "Memory Types=" << mModules[0].type << endl;
    stream << "Memory Speeds=" << mModules[0].type << endl;
    stream << "Memory Voltages=" << mModules[0].voltage << endl;
    return stream.str();
}

