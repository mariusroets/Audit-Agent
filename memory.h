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

        friend std::ostream& operator<<(std::ostream& stream, Memory& mem);

    protected:
        void read();

    private:
        std::string mType;
        int mSize;

};

#endif	// __MEMORY_H__

