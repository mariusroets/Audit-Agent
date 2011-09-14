/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __MACMEMORY_H__
#define __MACMEMORY_H__

#include <ostream>
#include "memory.h"

class MacMemory : public Memory
{
    public:
        MacMemory();
        ~MacMemory();

    protected:
        void read();

};

#endif	// __MACMEMORY_H__

