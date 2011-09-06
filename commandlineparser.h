/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __COMMANDLINEPARSER_H__
#define __COMMANDLINEPARSER_H__

#include <vector>
#include <string>

class CommandLineParser
{
    public:
        CommandLineParser(int argc, char *argv[]);
        void parse();

        // Data access
        bool help();
        bool daemon();
        bool passwordMode();
        std::string password();
        std::string daemonCommand();
        std::string command();


    private:
        std::vector<std::string> arguments;

        bool print_help;
        bool daemon_mode;
        bool password_mode;
        std::string daemon_command;
        std::string pwd;

};

#endif	// __COMMANDLINEPARSER_H__
