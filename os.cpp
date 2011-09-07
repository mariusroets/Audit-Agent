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
std::string OS::output()
{
    stringstream stream;
    stream << "OS Name=" << mName << mLineEnding;
    stream << "OS Major Version=" << mMajorVersion << mLineEnding;
    stream << "OS Minor Version=" << mMinorVersion << mLineEnding;
    stream << "OS Build=" << mBuild << mLineEnding;
    stream << "OS Service Pack=" << mServicePack << mLineEnding;
    stream << "OS Product ID=" << mProductId << mLineEnding;
    stream << "OS Product No=" << mProductNo << mLineEnding;
    return stream.str();
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
    stream << os.output();
    return stream;
}
