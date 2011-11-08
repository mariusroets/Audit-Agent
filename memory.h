/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <ostream>
#include <vector>
#include "info.h"
#include "memory.h"

class Memory : public Info
{
    public:
        struct MemModule {
            MemModule () {
                type = "";
                size = "";
                speed = "";
                voltage = "";
                status = "";
            }
            std::string type;
            std::string size;
            std::string speed;
            std::string voltage;
            std::string status;
        };
        Memory();
        ~Memory() {};
        std::string output();

    protected:
        vector<MemModule> mModules;
        int mSlots;
        int mSlotsUsed;
        double mTotalSize;

};

#endif	// __MEMORY_H__

