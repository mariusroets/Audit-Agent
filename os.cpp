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
    stream << "OS Name=" << mName << endl;
    stream << "OS Major Version=" << mMajorVersion << endl;
    stream << "OS Minor Version=" << mMinorVersion << endl;
    stream << "OS Build=" << mBuild << endl;
    stream << "OS Service Pack=" << mServicePack << endl;
    stream << "OS Product ID=" << mProductId << endl;
    stream << "OS Product No=" << mProductNo << endl;
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
