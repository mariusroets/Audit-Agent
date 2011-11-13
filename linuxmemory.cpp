
#include "linuxmemory.h"
#include "dmiparser.h"
#include "util.h"
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

LinuxMemory::LinuxMemory()
{
}
LinuxMemory::~LinuxMemory()
{
}
void LinuxMemory::read()
{
    mSlotsUsed = 0;
    DMIParser p(DMIParser::Memory);
    p.exec();
    mSlots = p.frameCount();
    for (int i = 0; i < mSlots; ++i) {
        p.setCurrentFrame(i);
        if (p["Size"] != "No Module Installed") {
            mModules.push_back(MemModule());
            std::vector<std::string> memFields;
            std::string size = p["Size"];
            boost::split(memFields, size, boost::is_any_of(SPACES), boost::token_compress_on);
            mSlotsUsed++;
            mModules[i].size = str(boost::format("%d %s") % memFields[0] % memFields[1]);
            mModules[i].type = p["Type"];
            mModules[i].speed = p["Speed"];
            // Calculate total size
            if (i == 0) {
                // The unit of the first slot determines the unit used
                mTotalSize = Size(mModules[i].size);
            } else {
                mTotalSize = mTotalSize + mModules[i].size;
            }
        }
    }
}
