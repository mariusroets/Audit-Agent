/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __LINUXSOFTWARE_H__
#define __LINUXSOFTWARE_H__

#include <iostream>
#include "software.h"

class LinuxSoftware : public Software
{
    public:
        LinuxSoftware();
        ~LinuxSoftware();

    protected:
        void read();

};

#endif	// __LINUXSOFTWARE_H__

