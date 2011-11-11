
#include <vector>
#include "macos.h"
#include "util.h"
#include "sysprofileparser.h"
#include <boost/algorithm/string.hpp>

MacOS::MacOS()
{
    read();
}
MacOS::~MacOS()
{
}
void MacOS::read()
{
    mName = SYS->value("Software:System Software Overview:System Version");
    boost::trim(mName);
    ///Mac OS X 10.5.8 (9L31a)
    std::vector<std::string> tokens;
    std::vector<std::string> versions;
    boost::split(tokens, mName, boost::is_any_of(" "));
    boost::split(versions, tokens[3], boost::is_any_of("."));

    mMajorVersion = versions[0];
    mMinorVersion = versions[1];
    mBuild = versions[2];
}
