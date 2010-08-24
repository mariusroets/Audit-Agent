/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <ostream>
#include <string>

#define SPACES " \t\r\n"

class Util
{
   public:
      Util();
      ~Util();

      static std::string exec(const std::string & cmd);
      static bool fileExists(const std::string & file);
      static void debugMsg(const std::string & msg);

};

#endif	// __UTIL_H__


