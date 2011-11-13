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
#include "size.h"

class Memory : public Info
{
    public:
        struct MemModule {
            MemModule () {
                type = "";
                size = Size();
                speed = "";
                voltage = "";
                status = "";
            }
            std::string type;
            Size size;
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
        Size mTotalSize;

};

#endif	// __MEMORY_H__

