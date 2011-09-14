/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __MACSOFTWARE_H__
#define __MACSOFTWARE_H__

#include <iostream>
#include "software.h"

class MacSoftware : public Software
{
    public:
        MacSoftware();
        ~MacSoftware();

    protected:
        void read();

};

#endif	// __MACSOFTWARE_H__

