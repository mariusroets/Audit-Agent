/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __ASSET_H__
#define __ASSET_H__

#include <iostream>
#include <ostream>
#include <string>
#include "info.h"

class Asset : public Info
{
   public:
      Asset();
      ~Asset();
      std::string output();
      std::string machineName();
      
   protected:
      std::string mMachineName;
      std::string mAssetNumber;
      std::string mScanComp;
      std::string mUser;
      std::string mNWUser;
      std::string mDescription;
      std::string mUniqueId;


};

#endif	// __ASSET_H__

