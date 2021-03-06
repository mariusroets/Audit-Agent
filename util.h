/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <vector>
#include <ostream>
#include <string>

#define SPACES " \t\r\n"

namespace Util
{
    struct Ftpdata {
        std::string address;
        std::string username;
        std::string password;
    };

    struct Settings {
        int sleep_time;
        std::string filename_base;
        std::string filename_ext;
        std::string encrypted_ext;
        std::string unique_id;
        std::string architecture;
        Ftpdata ftp;
        std::string install_path;
        std::string scan_comp;
        std::string log_dir;
        std::string version;
        bool all_software;
        bool encrypt;
        bool debug;
    };
    extern Settings *SETTINGS;

    std::string exec(const std::string & cmd);
    bool fileExists(const std::string & file);
    void debugMsg(const std::string & msg);
    void debugMsg(int msg);
    std::string shiftString(const std::string & input);
    void obfuscate(const std::string& in_filename);
    std::string getMachineName();

    // Templates

    template <class T>
        void showList(std::vector<T> list)
    {
        std::cout << list.size() << ":";
        for (int i = 0; i < (int)list.size(); i++) {
            std::cout << list[i] << ",";
        }
        std::cout << std::endl;
    }
}

#endif	// __UTIL_H__


