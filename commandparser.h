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
#include <map>

class CommandParser
{
    public:
        CommandParser();
        ~CommandParser();

        void parse(std::string cmd, std::string params = "", bool su = false );
        void split(std::string splitString);
        std::vector<std::string> lines();
        std::vector<std::vector<std::string> > fields();
        void printLines();
        void printFields();
        void init();

    private:
        std::vector<std::string>mLines;
        std::vector<std::vector<std::string> >mFields;
        std::map<std::string, std::string> mCmds;
};
extern CommandParser *CMD;

#endif	// __COMMANDPARSER_H__

