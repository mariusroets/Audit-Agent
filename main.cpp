
#include <boost/algorithm/string.hpp>
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
#include "commandparser.h"
#include "log.h"

#define ENCRYPTION_STRING "aL0NgrAnDoM$Tr1nG"
#define APPLICATION_NAME "lattitude-audit-agent"
#define EXECUTABLE_NAME "agent"

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

    return Util::getMachineName() + "_" + s->unique_id + "." + ext;
}

void writeData()
{

    std::string filename = createFilename();
    std::string filepath = "/tmp/" + filename;
    Util::Ftpdata f = Util::SETTINGS->ftp;
    InfoMiner im;
    if (filename.empty()) {
        std::cout << im;
    } else {
        // Write data to file
        OutputFile of(filepath);
        of.write(Util::SETTINGS->encrypt);
        // Ftp file
        if (!f.address.empty()) {
            ftplib conn;
            conn.Connect(f.address.c_str());
            conn.Login(f.username.c_str(), f.password.c_str());
            conn.Put(filepath.c_str(), filename.c_str(), ftplib::ascii);
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
}
 
/**
 * Initializes the application
 * Currently only detects the architecture
 */
void initFunction()
{
    // Initialize global logfile
    LogFile* l = Log::Instance();
    l->setFormat(LogFile::DateTimeStamped);
    l->setFilename(Util::SETTINGS->log_dir + "/application.log");
    l->setDebug(Util::SETTINGS->debug);
    l->writeLine("Logfile successffully initialized");
    
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
    if (Util::SETTINGS->debug) {
        CommandParser *parser = CommandParser::Instance();
        parser->parse( "dmidecode", "", true);
        std::vector<std::string> lines = parser->lines();
        for (unsigned int i = 0; i < lines.size() ; ++i) {
            l->writeDebug(lines[i]);
        }
    }
}

void readSettings()
{
    Util::SETTINGS = new Util::Settings;
    ConfigFile config("/etc/lattitude/configfile.cfg");
    Encryptor e(ENCRYPTION_STRING);
    Util::SETTINGS->sleep_time = config.getValueAsInt("CheckFrequency");
    Util::SETTINGS->filename_base = config.getValueAsString("FilenameBase");
    Util::SETTINGS->filename_ext = config.getValueAsString("FilenameExt");
    Util::SETTINGS->encrypted_ext = config.getValueAsString("EncryptedExt");
    Util::SETTINGS->ftp.address = config.getValueAsString("FtpAddress");
    Util::SETTINGS->ftp.username = config.getValueAsString("FtpUser");
    Util::SETTINGS->ftp.password = e.decrypt(config.getValueAsString("FtpPassword"));
    Util::SETTINGS->encrypt = config.getValueAsBool("EncryptFile");
    Util::SETTINGS->architecture = config.getValueAsString("Architecture");
    Util::SETTINGS->install_path = config.getValueAsString("InstallPath");
    Util::SETTINGS->all_software = config.getValueAsBool("AllSoftware");
    Util::SETTINGS->scan_comp = config.getValueAsString("ScanComp");
    Util::SETTINGS->log_dir = config.getValueAsString("LogPath");
    Util::SETTINGS->debug = config.getValueAsBool("Debug");
}

void readVersion()
{
    string file = Util::SETTINGS->install_path + "/version";
    std::ifstream in(file.c_str());
    if (!in) {
        Util::SETTINGS->version = "Unknown";
    } else {
        string line;
        in >> line;
        Util::SETTINGS->version = line;
    }
    LogFile *l = Log::Instance();
    l->writeLine("Version: " + Util::SETTINGS->version);
}


/**
 * Implements the main functionality
 */
void mainFunction()
{
    LogFile* l = Log::Instance();
    l->writeLine("Starting collection/write cycle");
    switch (ARCH->osType()) {
        case Architecture::Linux:
            // Do Linux stuff here
            break;
        case Architecture::Darwin:
            // Do Mac stuff here
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
    if (ARCH->osType() == Architecture::Darwin) {
        SysProfileParser::cleanUp();
    }
    l->writeLine("Completed collection/write cycle");
}

int main(int argc, char *argv[])
{
    //Util::obfuscate(std::string("audit.hsa"));
    //return 0;
    readSettings();
    initFunction();
    readVersion();

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
        Encryptor e(ENCRYPTION_STRING);
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
        Daemon *d = Daemon::daemon(APPLICATION_NAME);
        d->setExecutable(EXECUTABLE_NAME);
        string filebase = Util::SETTINGS->log_dir + "/" + APPLICATION_NAME;
        d->setFiles("/dev/null", filebase+".log", filebase+".err");
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
