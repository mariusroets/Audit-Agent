
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
#include "uniqueid.h"

#include <iterator>



void printUsage(std::string cmd)
{
    std::cout << "Usage: " << cmd << " [OPTIONS]" << std::endl;
    std::cout << "Options:\n";
    std::cout << "-d cmd: Starts the agent in daemon mode. cmd could be start|stop|status\n";
    std::cout << "-p password: Gives an encrypted version of 'password' and exits\n";

    std::cout << "-h : Prints this message, and exits\n";
}

std::string createFilename()
{
    Util::Settings *s = Util::SETTINGS;
    std::string ext = s->filename_ext;
    if (s->encrypt)
        ext = s->encrypted_ext;
    return s->filename_base + "_" + s->unique_id + "." + ext;
}

void writeData()
{
    std::string filename = createFilename();
    Util::Ftpdata f = Util::SETTINGS->ftp;
    InfoMiner im;
    if (filename.empty()) {
        std::cout << im;
    } else {
        // Write data to file
        OutputFile of(filename);
        of.write(Util::SETTINGS->encrypt);
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
    UniqueId id;
    Util::SETTINGS->unique_id = id.id();
}

void readSettings()
{
    Util::SETTINGS = new Util::Settings;
    ConfigFile config("configfile.cfg");
    Util::SETTINGS->sleep_time = config.getValueAsInt("CheckFrequency");
    Util::SETTINGS->filename_base = config.getValueAsString("FilenameBase");
    Util::SETTINGS->filename_ext = config.getValueAsString("FilenameExt");
    Util::SETTINGS->encrypted_ext = config.getValueAsString("EncryptedExt");
    Util::SETTINGS->ftp.address = config.getValueAsString("FtpAddress");
    Util::SETTINGS->ftp.username = config.getValueAsString("FtpUser");
    Util::SETTINGS->ftp.password = config.getValueAsString("FtpPassword");
    Util::SETTINGS->encrypt = config.getValueAsBool("EncryptFile");
    Util::SETTINGS->architecture = config.getValueAsString("Architecture");
    Util::SETTINGS->install_path = config.getValueAsString("InstallPath");
    Util::SETTINGS->all_software = config.getValueAsBool("AllSoftware");
    Util::SETTINGS->scan_comp = config.getValueAsString("ScanComp");
}


/**
 * Implements the main functionality
 */
void mainFunction()
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
    writeData();
}

int main(int argc, char *argv[])
{
    //Util::obfuscate(std::string("audit.hsa"));
    //return 0;
    readSettings();
    initFunction();

    // For parameters that need encryption
    Encryptor e("aL0NgrAnDoM$Tr1nG");
    // Variables used
    std::string daemoncmd = "";
    bool daemon = false;
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
                mainFunction();
                sleep(Util::SETTINGS->sleep_time);
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
        mainFunction();
    }

    cleanup();

    return 0;
}
