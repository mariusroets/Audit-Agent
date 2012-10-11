/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __LINUXHARDDRIVE_H__
#define __LINUXHARDDRIVE_H__

#include <vector>
#include <string>
#include <map>
#include "harddrive.h"

class LinuxHardDrive : public HardDrive
{
    public:
        LinuxHardDrive();
        ~LinuxHardDrive();

    protected:
        void read();

    private:
        void updatePartitionInfo();
        void updateDeviceInfo();

};

#endif	// __LINUXHARDDRIVE_H__

