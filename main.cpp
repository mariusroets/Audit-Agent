
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "infominer.h"
#include "daemon.h"

void printUsage(std::string cmd)
{
    std::cout << "Usage: " << cmd << " [OPTIONS]" << std::endl;
    std::cout << "Options:\n";
    std::cout << "-d cmd: Starts the agent in daemon mode. cmd could be start|stop|status\n";
    std::cout << "-f filename: Writes information to filename. If not specified, information is written to STDOUT\n";
    std::cout << "-h : Prints this message\n";

}

void writeData(std::string filename)
{
    InfoMiner im;
    if (filename.empty()) {
        std::cout << im;
    } else {
        std::ofstream of(filename.c_str());
        of << im;
        of.close();
    }
}

int main(int argc, char *argv[])
{
    std::string filename = "";
    std::string daemoncmd = "";
    bool daemon = false;
    bool help = false;
    int i = 1;
    while (i < argc) {
        if (std::string(argv[i]) == "-d") {
            if (i+1 >= argc) {
                printUsage(std::string(argv[0]));
                exit(2);
            }
            ++i;
            daemoncmd = std::string(argv[i]);
            daemon = true;
        }
        if (std::string(argv[i]) == "-h") {
            help = true;
        }
        if (std::string(argv[i]) == "-f") {
            if (i+1 >= argc) {
                printUsage(std::string(argv[0]));
                exit(2);
            }
            ++i;
            filename = std::string(argv[i]);
        }
        ++i;
    }
    if (help) {
        printUsage(std::string(argv[0]));
        exit(0);
    }
    if (daemon) {
        Daemon *d = Daemon::daemon("audit-agent");
        if (daemoncmd == "start") {
            if (!d->start()) {
                std::cout << "Could not start daemon: " << std::endl << d->statusStr() << std::endl;
                exit(2);
            }
            while (true) {
                writeData(filename);
                sleep(60);
            }
        } else if (daemoncmd == "stop") {
            d->stop();
        } else if (daemoncmd == "status") {
            std::cout << d->statusStr() << std::endl;
        } else {
            exit(2);
        }
        exit(0);
    }

    writeData(filename);

    return 0;
}
