
#define ASCII_MAX 255
#define EVEN_SHIFT 5
#define FAC3_SHIFT 9
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

    void debugMsg(int msg)
    {
        std::cerr << msg << std::endl;
    }

    /**
     * A string shifting function. 
     * This is no good for encryption. It serves only to deter the casual
     * glancer. Anybody that can write a program can break this in seconds
     * It was ported from a Delphi routine which did the following:
     *     - For even numbered indexes ascii values are shifted EVEN_SHIFT ahead (except for the highest EVEN_SHIFT ascii values)
     *     - Indexes which are a factor of 3 are shifted FAC3_SHIFT ahead (except for the highest FAC3_SHIFT ascii values)
     *     - If an index is both even and a factor of 3, it's shifted EVEN_SHIFT ahead (This part is incidental and dependant on code order)
     *     - All other characters are left intact
     * Since C++ uses 0 based indexes, 1 is added to the index before testing, in order to maintain compatibility
     */
    std::string shiftString(const std::string & input)
    {
        std::string output = input;
        for (int i = 0; i < (int)input.length(); i++) {
            if ((i+1) % 2 == 0) {
                if (input[i] <= ASCII_MAX - EVEN_SHIFT) {
                    output[i] += EVEN_SHIFT;
                }
            } else if ((i+1) % 3 == 0) {
                if (input[i] <= ASCII_MAX - FAC3_SHIFT) {
                    output[i] += FAC3_SHIFT;
                }
            }
        }
        return output;
    }

}
