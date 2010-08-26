/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __HARDDRIVE_H__
#define __HARDDRIVE_H__

#include <vector>
#include <string>
#include "info.h"

class HardDrive : public Info
{
    public:
        HardDrive();
        ~HardDrive();

    protected:
        void read();

    private:
        std::vector<std::string> mNames;

};

#endif	// __HARDDRIVE_H__

