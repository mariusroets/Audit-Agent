/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __COMMANDPARSER_H__
#define __COMMANDPARSER_H__

#include <string>
#include <vector>

class CommandParser
{
    public:
        CommandParser();
        ~CommandParser();

        std::vector<std::string> parse(std::string cmd);
        std::vector<std::vector<std::string> > split(std::string splitString);
        void printLines();
        void printFields();

    private:
        std::vector<std::string>mLines;
        std::vector<std::vector<std::string> >mFields;
};

#endif	// __COMMANDPARSER_H__

