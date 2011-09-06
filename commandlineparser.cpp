
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
    password_mode = false;
    daemon_command = "";
    pwd = "";
}
void CommandLineParser::parse()
{
    if (arguments.size() == 1)
        print_help = true;
    for (int i = 0; i < (int)arguments.size(); i++) {
        if ((arguments[i] == "-h") || (arguments[i] == "--help")) {
            print_help = true;
        } else if ((arguments[i] == "-d") || (arguments[i] == "--daemon")) {
            daemon_mode = true;
            daemon_command = arguments[i+1];
        } else if ((arguments[i] == "-p") || (arguments[i] == "--password")) {
            password_mode = true;
            pwd = arguments[i+1];
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

bool CommandLineParser::passwordMode()
{
    return password_mode;
}

std::string CommandLineParser::password()
{
    return pwd;
}
std::string CommandLineParser::daemonCommand()
{
    return daemon_command;
}
std::string CommandLineParser::command()
{
    return arguments[0];
}

