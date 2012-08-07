
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
            mSlotsUsed++;
            mModules[mSlotsUsed-1].size = Size(p["Size"]);
            mModules[mSlotsUsed-1].type = p["Type"];
            mModules[mSlotsUsed-1].speed = p["Speed"];
            // Calculate total size
            if (mSlotsUsed == 1) {
                // The unit of the first slot determines the unit used
                mTotalSize = Size(mModules[mSlotsUsed-1].size);
            } else {
                mTotalSize = mTotalSize + mModules[mSlotsUsed-1].size;
            }
        }
    }
}
