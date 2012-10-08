#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "cpu.h"


CPU::CPU()
{
    mInfoType = Info::CPU;
}
CPU::~CPU()
{
}

std::string CPU::output()
{
    stringstream stream;
    // Force speed to MHz regardless of what is reported
    mSpeed.convertTo(Size::MHz);

    stream << "CPU Speed=" << mSpeed << endl;
    stream << "CPU Vendor=" << mVendor << endl;
    stream << "CPU Type=" << mType << endl;
    stream << "CPU Count=" << mCount << endl;
    stream << "CPU Serial=" << mSerial << endl;
    stream << "CPU Codename=" << mCodename << endl;
    stream << "CPU ID String=" << mIdString << endl;
    stream << "CPU Reg String=" << mRegString << endl;

    return stream.str();
}

