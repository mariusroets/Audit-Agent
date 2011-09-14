/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __LINUXMEMORY_H__
#define __LINUXMEMORY_H__

#include <ostream>
#include "memory.h"

class LinuxMemory : public Memory
{
    public:
        LinuxMemory();
        ~LinuxMemory();

    protected:
        void read();

};

#endif	// __LINUXMEMORY_H__

