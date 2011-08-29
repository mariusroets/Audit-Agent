#include <vector>
#include <boost/algorithm/string.hpp>
#include "os.h"
#include "util.h"

OS::OS()
{
    read();
}
OS::~OS()
{
}

void OS::read()
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
std::ostream& operator<<(std::ostream& stream, OS& os)
{
    stream << "OS Name=" << os.mName << std::endl;
    stream << "OS Major Version=" << os.mMajorVersion << std::endl;
    stream << "OS Minor Version=" << os.mMinorVersion << std::endl;
    stream << "OS Build=" << os.mBuild << std::endl;
    stream << "OS Service Pack=" << os.mServicePack << std::endl;
    stream << "OS Product ID=" << os.mProductId << std::endl;
    stream << "OS Product No=" << os.mProductNo << std::endl;
    return stream;
}
