/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#include "monitor.h"

#ifndef __LINUXMONITOR_H__
#define __LINUXMONITOR_H__

class LinuxMonitor : public Monitor
{
    public:
        LinuxMonitor();
        ~LinuxMonitor();
    protected:
        void read();

};

#endif	// __LINUXMONITOR_H__
