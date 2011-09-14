#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "cpu.h"


CPU::CPU()
{
}
CPU::~CPU()
{
}

std::string CPU::output()
{
    stringstream stream;
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
std::ostream& operator<<(std::ostream& stream, CPU& cpu) 
{
    stream << cpu.output();
    return stream;
}

