
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
#include "architecture.h"
#include "sysprofileparser.h"
#include "util.h"

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

void writeData(std::string filename, ftpdata f, bool encrypt)
{
    InfoMiner im;
    if (filename.empty()) {
        std::cout << im;
    } else {
        // Write data to file
        OutputFile of(filename);
        of.write(encrypt);
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

/**
 * Function is executed before program exits.
 * Performs necessary cleanup
 */
void cleanup()
{
    // Delete global variables
    delete ARCH;
    delete SYS;
}
 
/**
 * Initializes the application
 * Currently only detects the architecture
 */
void initFunction()
{
    // Determine the architecture that we are working on
    // Variables determined here are used throughout the application
    // to make decisions on how to get information
    ARCH = new Architecture;
    switch (ARCH->osType()) {
        case Architecture::Linux:
            // Do Linux stuff here
            // cout << "This is Linux\n"; // For testing
            break;
        case Architecture::Darwin:
            // Do Mac stuff here
            // cout << "This is Mac\n"; // For testing
            SYS = new SysProfileParser;
            break;
        case Architecture::Unknown:
        default :
            cerr << "This is an unknown architecture\n";
            cerr << "Aborting\n";
            // Exit as the program will likely fail catastrophically somewhere
            cleanup();
            exit(1);
    }
}

/**
 * Implements the main functionality
 */
void mainFunction(std::string filename, ftpdata f, bool encrypt)
{
    switch (ARCH->osType()) {
        case Architecture::Linux:
            // Do Linux stuff here
            break;
        case Architecture::Darwin:
            // Do Mac stuff here
            SYS->parse();
            break;
        case Architecture::Unknown:
        default :
            cerr << "This is an unknown architecture\n";
            cerr << "Aborting\n";
            // Exit as the program will likely fail catastrophically somewhere
            cleanup();
            exit(1);
    }
    writeData(filename, f, encrypt);
}

int main(int argc, char *argv[])
{
    initFunction();

    // For parameters that need encryption
    Encryptor e("aL0NgrAnDoM$Tr1nG");
    // The configuration file
    ConfigFile config("configfile.cfg");
    // Variables used
    std::string filename = "";
    std::string daemoncmd = "";
    bool daemon = false;
    int sleep_time;
    ftpdata f;
    bool encrypt = false;
    // Parse command line parameters
    CommandLineParser cmd(argc, argv);
    cmd.parse();
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
    encrypt = config.getValueAsBool("EncryptFile");


    // Interaction with daemon process
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
                mainFunction(filename, f, encrypt);
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
    } else {
        mainFunction(filename, f, encrypt);
    }

    cleanup();

    return 0;
}
