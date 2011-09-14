/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __LINUXCPU_H__
#define __LINUXCPU_H__

#include <iostream>
#include <ostream>
#include <string>
#include "cpu.h"

class LinuxCPU : public CPU
{
   public:
      LinuxCPU();
      ~LinuxCPU();
    
   protected:
      void read();

};

#endif	// __LINUXCPU_H__

