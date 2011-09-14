/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __LINUXASSET_H__
#define __LINUXASSET_H__

#include <iostream>
#include <ostream>
#include <string>
#include "asset.h"

class LinuxAsset : public Asset
{
   public:
      LinuxAsset();
      ~LinuxAsset();
    
   protected:
      void read();

};

#endif	// __LINUXASSET_H__

