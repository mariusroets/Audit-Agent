/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __MACASSET_H__
#define __MACASSET_H__

#include <iostream>
#include <ostream>
#include <string>
#include "asset.h"

class MacAsset : public Asset
{
   public:
      MacAsset();
      ~MacAsset();
    
   protected:
      void read();

};

#endif	// __MACASSET_H__

