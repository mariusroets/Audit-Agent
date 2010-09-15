/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __FTP_H__
#define __FTP_H__

#include <string>
#include <vector>

#define USR ""
#define PWD ""
#define ADDR ""
#define SCRIPT_FILE "/tmp/agent-send-script.ftp"

class Ftp
{
    public:
        Ftp(std::string address="", std::string username="", std::string password="");
        ~Ftp();

        void send();
        void addFileToSend(const std::string& file);
        void clearFileList();

    private:
        std::string mAddress;
        std::string mUsername;
        std::string mPassword;
        std::string mScriptFile;
        std::vector<std::string> mFiles;

        void createScriptFile();
        void removeScriptFile();

};

#endif	// __FTP_H__

