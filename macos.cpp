
#include <vector>
#include "macos.h"
#include "util.h"
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
    mName = Util::exec("uname -s");
    boost::trim(mName);
    std::string s = Util::exec("uname -r");
    boost::trim(s);
    std::vector<std::string> tokens;
    boost::split(tokens, s, boost::is_any_of("."));
    mMajorVersion = tokens[0];
    mMinorVersion = tokens[1];
    mBuild = tokens[2];
}
