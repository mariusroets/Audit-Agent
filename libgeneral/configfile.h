/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef __CONFIGFILE_H__
#define __CONFIGFILE_H__

#include "delimitedfile.h"

class ConfigFile : public DelimitedFile
{
    public:
        ConfigFile(const std::string& f);
        std::string getValueAsString(const std::string name); 
        int getValueAsInt(const std::string name); 
        bool getValueAsBool(const std::string name);
};

#endif	// __CONFIGFILE_H__

