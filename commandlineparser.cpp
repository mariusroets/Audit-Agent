
#include <iostream>
#include <cstdlib>
#include "commandlineparser.h"

CommandLineParser::CommandLineParser(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++) {
        arguments.push_back(argv[i]);
    }
    // Set default options
    print_help = false;
    daemon_mode = false;
    daemon_command = "";
    file = "";
    ftp_address = "";
    ftp_user = "";
    ftp_password = "";
    check_time = 60;
}
void CommandLineParser::parse()
{
    if (arguments.size() == 1)
        print_help = true;
    for (int i = 0; i < (int)arguments.size(); i++) {
        std::cout << arguments[i] << std::endl;
        if ((arguments[i] == "-h") || (arguments[i] == "--help")) {
            print_help = true;
        } else if ((arguments[i] == "-d") || (arguments[i] == "--daemon")) {
            daemon_mode = true;
            daemon_command = arguments[i+1];
        } else if ((arguments[i] == "-f") || (arguments[i] == "--filename")) {
            file = arguments[i+1];
        } else if ((arguments[i] == "-a") || (arguments[i] == "--address")) {
            ftp_address = arguments[i+1];
        } else if ((arguments[i] == "-u") || (arguments[i] == "--user")) {
            ftp_user = arguments[i+1];
        } else if ((arguments[i] == "-p") || (arguments[i] == "--password")) {
            ftp_password = arguments[i+1];
        } else if ((arguments[i] == "-s") || (arguments[i] == "--check-time")) {
            check_time = atoi(arguments[i+1].c_str());
        }
        
    }


}
bool CommandLineParser::help()
{
    return print_help;
}

bool CommandLineParser::daemon()
{
    return daemon_mode;
}

std::string CommandLineParser::filename()
{
    return file;
}

std::string CommandLineParser::ftpaddress()
{
    return ftp_address;
}

std::string CommandLineParser::ftpuser()
{
    return ftp_user;
}

std::string CommandLineParser::ftppassword()
{
    return ftp_password;
}
std::string CommandLineParser::daemonCommand()
{
    return daemon_command;
}
std::string CommandLineParser::command()
{
    return arguments[0];
}
int CommandLineParser::sleepTime()
{
    return check_time;
}

