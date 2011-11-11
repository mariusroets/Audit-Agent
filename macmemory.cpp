
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
    SysProfileParser p;
    p.parse();
    mTotalSize = 0;
    vector<string> slots = p.children("Memory");
    mSlots = slots.size();
    mSlotsUsed = 0;
    for (int i = 0; i < (int)slots.size(); i++) {
        string key_base = string("Memory") + ":" + slots[i] + ":";
        string key = key_base + "Size";
        mModules.push_back(MemModule());
        mModules[i].size = p.value(key);
        addMemoryToTotal(mModules[i].size);
        key = key_base + "Type";
        mModules[i].type = p.value(key);
        key = key_base + "Speed";
        mModules[i].speed = p.value(key);
        // This should be conditional, but I don't know what the condition is
        // since I don't have a Mac with open slots?
        mSlotsUsed++;
        
    }

}
void MacMemory::addMemoryToTotal(const string& mem)
{
    vector<string> fields;
    boost::split(fields, mem, boost::is_any_of(" "), boost::token_compress_on);
    if (fields[1] == "GB") {
        mTotalSize += atof(fields[0].c_str());
    } else if (fields[1] == "MB") {
        mTotalSize += atof(fields[0].c_str())/1000;
    }
}
