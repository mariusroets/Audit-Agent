#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "cpu.h"


CPU::CPU()
{
    read();
}
CPU::~CPU()
{
}

std::string CPU::output()
{
    stringstream stream;
    stream << "CPU Speed=" << mSpeed << mLineEnding;
    stream << "CPU Vendor=" << mVendor << mLineEnding;
    stream << "CPU Type=" << mType << mLineEnding;
    stream << "CPU Count=" << mCount << mLineEnding;
    stream << "CPU Serial=" << mSerial << mLineEnding;
    stream << "CPU Codename=" << mCodename << mLineEnding;
    stream << "CPU ID String=" << mIdString << mLineEnding;
    stream << "CPU Reg String=" << mRegString << mLineEnding;

    return stream.str();
}
void CPU::read()
{
    std::string line;
    std::ifstream file ("/proc/cpuinfo");
    if (file.is_open()) {
        while (!file.eof()) {
            getline (file, line);
            boost::trim(line);
            // Skip empty lines
            if (line.empty())
                continue;
            std::vector<std::string> tokens;
            boost::split(tokens, line, boost::is_any_of(":"));
            // Skip lines with no information (just one field)
            if (tokens.size() < 2)
                continue;
            // Remove whitespace
            boost::trim(tokens[0]);
            boost::trim(tokens[1]);
            // Populate data members
            if (tokens[0] == "vendor_id") {
                mVendor = tokens[1];
            } else if (tokens[0] == "cpu cores") {
                mCount = atoi(tokens[1].c_str());
            } else if (tokens[0] == "cpu MHz") {
                mSpeed = atoi(tokens[1].c_str());
            } else if (tokens[0] == "CPU Reg String") {
                mRegString = tokens[1];
            }

        }
    }
	
}
std::ostream& operator<<(std::ostream& stream, CPU& cpu) 
{
    stream << cpu.output();
    return stream;
}

