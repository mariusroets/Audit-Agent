#include <vector>
#include <boost/algorithm/string.hpp>
#include "os.h"
#include "util.h"

OS::OS()
{
    mInfoType = Info::OS;
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

