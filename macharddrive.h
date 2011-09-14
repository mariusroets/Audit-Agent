/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __MACHARDDRIVE_H__
#define __MACHARDDRIVE_H__

#include <vector>
#include <string>
#include <map>
#include "harddrive.h"

class MacHardDrive : public HardDrive
{
    public:
        MacHardDrive();
        ~MacHardDrive();

    protected:
        void read();

};

#endif	// __MACHARDDRIVE_H__

