
#include <stdio.h>
#include <sys/stat.h>
#include "util.h"

namespace Util
{
    std::string exec(const std::string & cmd)
    {
        FILE* pipe = popen(cmd.c_str(), "r");
        if (!pipe) return "ERROR";
        char buffer[128];
        std::string result = "";
        while(!feof(pipe)) {
            if(fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
        pclose(pipe);
        return result;
    }

    bool fileExists(const std::string & file)
    {
        struct stat stFileInfo;
        int intStat;

        // Attempt to get the file attributes
        intStat = stat(file.c_str(),&stFileInfo);
        if(intStat == 0) {
            // We were able to get the file attributes
            // so the file obviously exists.
            return true;
        } else {
            // We were not able to get the file attributes.
            // This may mean that we don't have permission to
            // access the folder which contains this file.
            return false;
        }

    }

    void debugMsg(const std::string & msg)
    {
        std::cerr << msg << std::endl;
    }
}
