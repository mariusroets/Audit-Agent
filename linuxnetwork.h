/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#include "network.h"

#ifndef __LINUXNETWORK_H__
#define __LINUXNETWORK_H__

class LinuxNetwork : public Network
{
    public:
        LinuxNetwork();
        ~LinuxNetwork();
    protected:
        void read();

};

#endif	// __LINUXNETWORK_H__

