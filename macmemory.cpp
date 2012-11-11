
#include "macmemory.h"
#include "dmiparser.h"
#include "util.h"
#include "sysprofileparser.h"
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

MacMemory::MacMemory()
{
}
MacMemory::~MacMemory()
{
}
void MacMemory::read()
{
    SysProfileParser *sys = SysProfileParser::Instance();
    vector<string> slots = sys->children("Memory");
    mSlots = slots.size();
    mSlotsUsed = 0;
    for (int i = 0; i < (int)slots.size(); i++) {
        string key_base = string("Memory") + ":" + slots[i] + ":";
        string key = key_base + "Size";
        mModules.push_back(MemModule());
        mModules[i].size.set(sys->value(key));
        key = key_base + "Type";
        mModules[i].type = sys->value(key);
        key = key_base + "Speed";
        mModules[i].speed = sys->value(key);
        // This should be conditional, but I don't know what the condition is
        // since I don't have a Mac with open slots?
        mSlotsUsed++;
        // Calculate total size
        if (i == 0) {
            // The unit of the first slot determines the unit used
            mTotalSize = Size(mModules[i].size);
        } else {
            mTotalSize = mTotalSize + mModules[i].size;
        }
        
    }

}
