/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __MACOS_H__
#define __MACOS_H__

#include <ostream>
#include <string>
#include "os.h"

class MacOS : public OS
{
    public:
        MacOS();
        ~MacOS();

    protected:
        void read();

};

#endif	// __MACOS_H__

