/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __MACSYSTEM_H__
#define __MACSYSTEM_H__

#include <ostream>
#include "system.h"

class MacSystem : public System
{
    public:
        MacSystem();
        ~MacSystem();

    protected:
        void read();

};

#endif	// __MACSYSTEM_H__

