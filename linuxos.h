/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __LINUXOS_H__
#define __LINUXOS_H__

#include <ostream>
#include <string>
#include "os.h"

class LinuxOS : public OS
{
    public:
        LinuxOS();
        ~LinuxOS();

    protected:
        void read();

};

#endif	// __LINUXOS_H__

