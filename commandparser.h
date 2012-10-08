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
        static CommandParser* Instance();

        void parse(std::string cmd, std::string params = "", bool su = false );
        void split(std::string splitString);
        std::vector<std::string> lines();
        std::vector<std::vector<std::string> > fields();
        void printLines();
        void printFields();
        void init();

    private:
        CommandParser();
        ~CommandParser();
        static void cleanUp();
        static CommandParser* mInstance;
        // Not copyable
        CommandParser(CommandParser const&);
        CommandParser operator=(CommandParser const&);

        std::vector<std::string>mLines;
        std::vector<std::vector<std::string> >mFields;
        std::map<std::string, std::string> mCmds;
};

#endif	// __COMMANDPARSER_H__

