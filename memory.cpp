
#include <stdio.h>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>
#include "memory.h"
#include "dmiparser.h"
#include "util.h"


Memory::Memory()
{
    mInfoType = Info::Memory;
}

std::string Memory::output()
{
    mTotalSize.convertTo(Size::MB);
    stringstream stream;
    stream << "Memory=" << mTotalSize << endl;
    stream << "Memory Slots Used=" << mSlotsUsed << endl;
    stream << "Memory Slots Free=" << mSlots-mSlotsUsed << endl;
    stream << "Memory Max Size=" << mTotalSize << endl;
    // Using values for the first non empty memory module. Typically, they should
    // be the same for all modules, but it would have been useful if the file 
    // format allowed for reporting on differences since this is a big cause of 
    // system instability.
    if (mModules.size() > 0) {
        stream << "Memory Types=" << mModules[0].type << endl;
        stream << "Memory Speeds=" << mModules[0].speed << endl;
        stream << "Memory Voltages=" << mModules[0].voltage << endl;
    }
    stream << endl << endl;

    stream << "Memory Chips Count=" << mModules.size() << endl;
    for (int i = 0; i < (int)mModules.size(); i++) {
        stream << "Memory Chips ID=Chip" << i+1 << endl;
        stream << "Memory Chips Size" << i+1 << "=" << mModules[i].size << endl;
        stream << "Memory Chips Type" << i+1 << "=" << mModules[i].type << endl;
        stream << "Memory Chips Type Detail" << i+1 << "=" << mModules[i].type_detail << endl;
        stream << "Memory Chips Form Factor" << i+1 << "=" << mModules[i].form_factor << endl;
        stream << "Memory Chips Speed" << i+1 << "=" << mModules[i].speed << endl;
        stream << "Memory Chips Slot" << i+1 << "=" << mModules[i].slot << endl;
        stream << "Memory Chips Serial" << i+1 << "=" << mModules[i].serial << endl;
        stream << "Memory Chips Asset Tag" << i+1 << "=" << mModules[i].asset_tag << endl;
        stream << "Memory Chips Manufacturer" << i+1 << "=" << mModules[i].manufacturer << endl;
        stream << "Memory Chips Part Number" << i+1 << "=" << mModules[i].part_number << endl;
    }

    return stream.str();
}

