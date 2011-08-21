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
        std::string filename();
        std::string ftpaddress();
        std::string ftpuser();
        std::string ftppassword();
        std::string daemonCommand();
        std::string command();
        int sleepTime();


    private:
        std::vector<std::string> arguments;

        bool print_help;
        bool daemon_mode;
        int check_time;
        std::string daemon_command;
        std::string file;
        std::string ftp_address;
        std::string ftp_user;
        std::string ftp_password;

};

#endif	// __COMMANDLINEPARSER_H__
