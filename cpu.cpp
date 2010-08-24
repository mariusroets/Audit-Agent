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
    stream << "CPU Speed=" << cpu.mSpeed << std::endl;
    stream << "CPU Vendor=" << cpu.mVendor << std::endl;
    stream << "CPU Type=" << cpu.mType << std::endl;
    stream << "CPU Count=" << cpu.mCount << std::endl;
    stream << "CPU Serial=" << cpu.mSerial << std::endl;
    stream << "CPU Codename=" << cpu.mCodename << std::endl;
    stream << "CPU ID String=" << cpu.mIdString << std::endl;
    stream << "CPU Reg String=" << cpu.mRegString << std::endl;
    return stream;
}

