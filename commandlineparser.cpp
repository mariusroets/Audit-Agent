
#include <iostream>
#include "commandlineparser.h"

CommandLineParser::CommandLineParser(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++) {
        arguments.push_back(argv[i]);
    }
    // Set default options
    mHelp = false;
    mDaemon = false;
    mDaemonCommand = "";
    mFilename = "";
    mFtpaddress = "";
    mFtpuser = "";
    mFtppassword = "";
}
void CommandLineParser::parse()
{
    for (int i = 0; i < (int)arguments.size(); i++) {
        std::cout << arguments[i] << std::endl;
        if ((arguments[i] == "-h") || (arguments[i] == "--help")) {
            mHelp = true;
        } else if ((arguments[i] == "-d") || (arguments[i] == "--daemon")) {
            mDaemon = true;
            mDaemonCommand = arguments[i+1];
        } else if ((arguments[i] == "-f") || (arguments[i] == "--filename")) {
            mFilename = arguments[i+1];
        } else if ((arguments[i] == "-a") || (arguments[i] == "--address")) {
            mFtpaddress = arguments[i+1];
        } else if ((arguments[i] == "-u") || (arguments[i] == "--user")) {
            mFtpuser = arguments[i+1];
        } else if ((arguments[i] == "-p") || (arguments[i] == "--password")) {
            mFtppassword = arguments[i+1];
        }
        
    }


}
bool CommandLineParser::help()
{
    return mHelp;
}

bool CommandLineParser::daemon()
{
    return mDaemon;
}

std::string CommandLineParser::filename()
{
    return mFilename;
}

std::string CommandLineParser::ftpaddress()
{
    return mFtpaddress;
}

std::string CommandLineParser::ftpuser()
{
    return mFtpuser;
}

std::string CommandLineParser::ftppassword()
{
    return mFtppassword;
}
std::string CommandLineParser::daemonCommand()
{
    return mDaemonCommand;
}

