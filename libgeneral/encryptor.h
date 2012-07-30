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

#ifndef __ENCRYPTOR_H__
#define __ENCRYPTOR_H__

#include <string>

using namespace std;

class Encryptor
{
    public:
        Encryptor(const string& key);
        string decrypt(const string& encrypted);
        string encrypt(const string& plain_text);

    private:
        string mKey;

        string makeHexString(unsigned int offset, const string& str);
        string makeAsciiString(unsigned int &offset, const string& str);
        int getOffset(const string& str);
        
};

#endif	// __ENCRYPTOR_H__

