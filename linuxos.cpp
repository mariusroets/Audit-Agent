
#include <vector>
#include "linuxos.h"
#include "util.h"
#include <boost/algorithm/string.hpp>

LinuxOS::LinuxOS()
{
    read();
}
LinuxOS::~LinuxOS()
{
}
void LinuxOS::read()
{
    mName = Util::exec("uname -s");
    boost::trim(mName);
    std::string s = Util::exec("uname -r");
    boost::trim(s);
    std::vector<std::string> tokens;
    boost::split(tokens, s, boost::is_any_of("."));
    mMajorVersion = tokens[0];
    mMinorVersion = tokens[1];
    mBuild = tokens[2];
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
