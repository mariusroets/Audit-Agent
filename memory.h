/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <ostream>
#include "info.h"
#include "memory.h"

class Memory : public Info
{
    public:
        Memory();
        ~Memory() {};
        std::string output();

        friend std::ostream& operator<<(std::ostream& stream, Memory& mem);

    protected:
        std::string mType;
        std::string mSize;
        int mSlots;
        int mSlotsUsed;
        std::string mSpeed;
        std::string mVoltage;

};

#endif	// __MEMORY_H__

