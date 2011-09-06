
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include "infominer.h"
#include "daemon.h"
#include "commandlineparser.h"
#include "outputfile.h"
#include "ftplib/ftplib.h"
#include "configfile.h"
#include "encryptor.h"

#include <iterator>


struct ftpdata {
    std::string address;
    std::string username;
    std::string password;
};

void printUsage(std::string cmd)
{
    std::cout << "Usage: " << cmd << " [OPTIONS]" << std::endl;
    std::cout << "Options:\n";
    std::cout << "-d cmd: Starts the agent in daemon mode. cmd could be start|stop|status\n";
    std::cout << "-p password: Gives an encrypted version of 'password' and exits\n";

    std::cout << "-h : Prints this message, and exits\n";
}

void writeData(std::string filename, ftpdata f)
{
    InfoMiner im;
    if (filename.empty()) {
        std::cout << im;
    } else {
        // Write data to file
        OutputFile of(filename);
        of.write();
        // Ftp file
        if (!f.address.empty()) {
            ftplib conn;
            conn.Connect(f.address.c_str());
            conn.Login(f.username.c_str(), f.password.c_str());
            conn.Put(filename.c_str(), "audit.txt", ftplib::ascii);
            conn.Quit();
        }
    }
}

int main(int argc, char *argv[])
{
    //
    Encryptor e("aL0NgrAnDoM$Tr1nG");
    ConfigFile config("configfile.cfg");
    std::string filename = "";
    std::string daemoncmd = "";
    bool daemon = false;
    int sleep_time;
    ftpdata f;
    CommandLineParser cmd(argc, argv);
    cmd.parse();


    // Parse command line options
    if (cmd.help()) {
        printUsage(argv[0]);
        return 0;
    }
    if (cmd.passwordMode()) {
        cout << e.encrypt(cmd.password()) << endl;
        return 0;
    }
    if (cmd.daemon()) {
        daemon = true;
        daemoncmd = cmd.daemonCommand();
    }
    sleep_time = config.getValueAsInt("CheckFrequency");
    filename = config.getValueAsString("Filename");
    f.address = config.getValueAsString("FtpAddress");
    f.username = config.getValueAsString("FtpUser");
    f.password = config.getValueAsString("FtpPassword");

    // This will start/stop/status the daemon process
    if (daemon) {
        Daemon *d = Daemon::daemon("audit-agent");
        if (daemoncmd == "start") {
            if (!d->start()) {
                std::cout << "Could not start daemon: " << std::endl << d->statusStr() << std::endl;
                return 2;
            }
            // The main daemon loop
            while (true) {
                writeData(filename, f);
                sleep(sleep_time);
            }
        } else if (daemoncmd == "stop") {
            d->stop();
        } else if (daemoncmd == "status") {
            std::cout << d->statusStr() << std::endl;
        } else {
            return 2;
        }
        return 0;
    }

    writeData(filename, f);

    return 0;
}
