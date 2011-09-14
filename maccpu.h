/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __MACCPU_H__
#define __MACCPU_H__

#include <iostream>
#include <ostream>
#include <string>
#include "cpu.h"

class MacCPU : public CPU
{
   public:
      MacCPU();
      ~MacCPU();
    
   protected:
      void read();

};

#endif	// __MACCPU_H__

