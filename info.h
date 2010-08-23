/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __INFO_H__
#define __INFO_H__

#include <iostream>
#include <ostream>
#include <string>

class Info
{
   public:
      Info() {};
      ~Info() {};
      
   protected:
      virtual void read() =0;

};

#endif	// __INFO_H__
