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
                size = Size();
                type = "";
                type_detail = "";
                form_factor = "";
                speed = "";
                slot = "";
                serial = "";
                asset_tag = "";
                manufacturer = "";
                part_number = "";
                voltage = "";
                status = "";
            }
            Size size;
            std::string type;
            std::string type_detail;
            std::string form_factor;
            std::string speed;
            std::string slot;
            std::string serial;
            std::string asset_tag;
            std::string manufacturer;
            std::string part_number;
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

