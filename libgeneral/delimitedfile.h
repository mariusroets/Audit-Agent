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

#ifndef __DELIMITEDFILE_H__
#define __DELIMITEDFILE_H__

#include <string>
#include <vector>
#include <set>

class DelimitedFile
{
    public:
        DelimitedFile(const std::string& f);
        void setDelimiters(std::set<char> delim);
        void setCommentChars(std::set<char> c);
        void first();
        bool next();
        bool previous();
        int count() const;
        void read();

        int asInt(int index);
        int asDouble(int index);
        bool asBool(int index);
        std::string operator[](int i);

        // Debug
        void showCommentChars();
        void showDelimiters();
        void showSet(std::set<char> s);

    protected:
        void tokenize(const std::string& line);

    private:
        std::string filename;
        std::vector<std::string> fields;
        std::set<char> delimiters;
        std::set<char> commentChars;
        std::vector<std::vector<std::string> > lines;
        int index;

};

#endif	// __DELIMITEDFILE_H__

