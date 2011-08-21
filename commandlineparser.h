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


    private:
        std::vector<std::string> arguments;

        bool mHelp;
        bool mDaemon;
        std::string mDaemonCommand;
        std::string mFilename;
        std::string mFtpaddress;
        std::string mFtpuser;
        std::string mFtppassword;

};

#endif	// __COMMANDLINEPARSER_H__
