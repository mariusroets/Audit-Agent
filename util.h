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

namespace Util
{
    std::string exec(const std::string & cmd);
    bool fileExists(const std::string & file);
    void debugMsg(const std::string & msg);
    void debugMsg(int msg);
}

#endif	// __UTIL_H__


