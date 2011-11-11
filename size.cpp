
#include <vector>
#include "size.h"
#include <boost/algorithm/string.hpp>

Size::Size()
{
}

Size::Size(const string& s)
{
    parse(s);
}

void Size::parse(const string& s)
{
    vector<string> fields;
    boost::split(fields, s, boost::is_any_of(" "), boost::token_compress_on);
    if (fields.size() != 2) {
        mValue = 0;
        mUnit = Size::Unknown;
    } else {
        mValue = atof(fields[0].c_str());
        mUnit = determineUnit(fields[1]);
    }
}

Size::Unit Size::determineUnit(const string& u)
{
    if (mUnitStringMap.find(u) != mUnitStringMap.end())
        return mUnitStringMap[u];

    return Size::Unknown;
}
void Size::init()
{
    mUnitStringMap["GB"] = Size::GB;
    mUnitStringMap["MB"] = Size::MB;
    mUnitStringMap["KB"] = Size::KB;
    mUnitStringMap["TB"] = Size::TB;
    mUnitStringMap["Unknown"] = Size::Unknown;
    mUnitStringReverseMap[Size::GB] = "GB";
    mUnitStringReverseMap[Size::MB] = "MB";
    mUnitStringReverseMap[Size::KB] = "KB";
    mUnitStringReverseMap[Size::TB] = "TB";
    mUnitStringReverseMap[Size::Unknown] = "Unknown";
}

std::ostream& operator<<(std::ostream& stream, Size& s)
{
    stream << s.mValue << " " << s.mUnitStringReverseMap[s.mUnit];
    return stream;
}
