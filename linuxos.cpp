
#include <vector>
#include "linuxos.h"
#include "util.h"
#include "commandparser.h"
#include <boost/algorithm/string.hpp>

LinuxOS::LinuxOS()
{
}
LinuxOS::~LinuxOS()
{
}
void LinuxOS::read()
{

    mName = Util::exec("uname -s");
    boost::trim(mName);
    std::string kernel = Util::exec("uname -r");
    boost::trim(kernel);
    std::vector<std::string> tokens;
    boost::split(tokens, kernel, boost::is_any_of("."));
    mMajorVersion = tokens[0];
    mMinorVersion = tokens[1];
    mBuild = tokens[2];


    CommandParser c;
    c.parse("lsb_release", " -a");
    c.split(":");
    std::vector<std::vector<std::string> > fields2 = c.fields();
    for (unsigned int i = 0; i < fields2.size() ; ++i) {
        if (fields2[i].size() <= 0)
            continue;
        if (fields2[i][0] == "Description") {
            mName = fields2[i][1];
        }
        if (fields2[i][0] == "Release") {
            mMajorVersion = fields2[i][1];
            mMinorVersion = "";
            mBuild = kernel;
        }
    }

    c.parse("cat", "/etc/*-release");
    c.split("=");
    std::vector<std::vector<std::string> > fields = c.fields();
    for (unsigned int i = 0; i < fields.size() ; ++i) {
        if (fields[i].size() <= 0)
            continue;
        if (fields[i][0] == "PATCHLEVEL") {
            mMinorVersion = fields[i][1];
        }
    }
    
    /*
     * Slackware: /etc/slackware-version
Mandrake: /etc/mandrake-release
Red Hat: /etc/redhat-release
Fedora: /etc/fedora-release
Suse :  /etc/SuSE-release
United : /etc/UnitedLinux-release
Debian : /etc/debian_version
*/
}
