
#include "linuxmemory.h"
#include "dmiparser.h"
#include "util.h"
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

LinuxMemory::LinuxMemory()
{
    read();
}
LinuxMemory::~LinuxMemory()
{
}
void LinuxMemory::read()
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
