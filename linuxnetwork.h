/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __LINUXNETWORK_H__
#define __LINUXNETWORK_H__

#include "network.h"

class LinuxNetwork : public Network
{
    public:
        LinuxNetwork();
        ~LinuxNetwork();
    protected:
        void read();

};

#endif	// __LINUXNETWORK_H__

