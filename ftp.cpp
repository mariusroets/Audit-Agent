
#include <iostream>
#include <fstream>
#include "ftp.h"
#include "util.h"

Ftp::Ftp(std::string address, std::string username, std::string password)
{
    if (address.empty())
        mAddress = ADDR;
    else
        mAddress = address;
    if (username.empty())
        mUsername = USR;
    else
        mUsername = username;
    if (password.empty())
        mPassword = PWD;
    else
        mPassword = password;

}
Ftp::~Ftp()
{
}
void Ftp::addFileToSend(const std::string& file)
{
    mFiles.push_back(file);
}
void Ftp::send()
{
    createScriptFile();
    Util::exec(std::string("ftp -n <") + SCRIPT_FILE);
    removeScriptFile();
}
void Ftp::clearFileList()
{
    mFiles.clear();
}
void Ftp::createScriptFile()
{
    std::ofstream out(SCRIPT_FILE);
    out << "open " << mAddress << std::endl;
    out << "passive on\n";
    out << "user " << mUsername << " " << mPassword << std::endl;
    for (int i = 0; i < (int)mFiles.size(); ++i)
        out << "put " << mFiles[i] << std::endl;
    
    out << "quit\n";
    out.close();

}
void Ftp::removeScriptFile()
{
    Util::exec(std::string("rm ") + SCRIPT_FILE);
}
