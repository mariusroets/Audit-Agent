/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#include "monitor.h"

#ifndef __MACMONITOR_H__
#define __MACMONITOR_H__

class MacMonitor : public Monitor
{
    public:
        MacMonitor();
        ~MacMonitor();
    protected:
        void read();

};

#endif	// __MACMONITOR_H__
