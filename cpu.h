/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __CPU_H__
#define __CPU_H__

#include <iostream>
#include <ostream>
#include <string>
#include "info.h"

class CPU : public Info
{
   public:
      CPU();
      ~CPU();
      std::string output();
      
   protected:
      int mCount;
      std::string mSpeed;
      std::string mVendor;
      std::string mType;
      std::string mSerial;
      std::string mCodename;
      std::string mIdString;
      std::string mRegString;


};

#endif	// __CPU_H__

