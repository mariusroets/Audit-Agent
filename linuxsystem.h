/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __LINUXSYSTEM_H__
#define __LINUXSYSTEM_H__

#include <ostream>
#include "system.h"

class LinuxSystem : public System
{
    public:
        LinuxSystem();
        ~LinuxSystem();

    protected:
        void read();

};

#endif	// __LINUXSYSTEM_H__

