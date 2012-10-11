
#include <vector>
#include <iostream>
#include <cmath>
#include "size.h"
#include <boost/algorithm/string.hpp>

Size::Size()
{
    init();
    clear();
}

Size::Size(const string& s)
{
    init();
    set(s);
}
Size::Size(const Size& s) : mValue(s.mValue), mUnit(s.mUnit)
{
    init();
}

void Size::set(const string& s)
{
    parse(s);
}

void Size::clear()
{
    mValue = 0;
    mUnit = Size::Unknown;
}

void Size::parse(const string& s)
{
    if (s.empty()) {
        clear();
        return;
    }

    size_t pos = s.find_first_of(" ");
    if (pos == string::npos) {
        pos = s.find_first_of("K");
    }
    if (pos == string::npos) {
        pos = s.find_first_of("M");
    }
    if (pos == string::npos) {
        pos = s.find_first_of("G");
    }
    if (pos == string::npos) {
        pos = s.find_first_of("T");
    }
    if (pos == string::npos) {
        pos = s.find_first_of("B");
    }
    if (pos == string::npos) {
        clear();
        return;
    } else {
        mValue = atof(s.substr(0, pos).c_str());
        mUnit = determineUnit(s.substr(pos));
    }
}

Size::Unit Size::determineUnit(const string& u)
{
    string u2 = u;
    boost::trim(u2);
    if (mUnitStringMap.find(u2) != mUnitStringMap.end())
        return mUnitStringMap[u2];

    // If we don't know the unit, it makes no sense to store a value
    clear();
    return Size::Unknown;
}
void Size::init()
{
    mUnitStringMap["GB"] = Size::GB;
    mUnitStringMap["MB"] = Size::MB;
    mUnitStringMap["MBytes"] = Size::MB;
    mUnitStringMap["KB"] = Size::KB;
    mUnitStringMap["TB"] = Size::TB;
    mUnitStringMap["G"] = Size::GB;
    mUnitStringMap["M"] = Size::MB;
    mUnitStringMap["K"] = Size::KB;
    mUnitStringMap["T"] = Size::TB;
    mUnitStringMap["B"] = Size::B;
    mUnitStringMap["Hz"] = Size::Hz;
    mUnitStringMap["KHz"] = Size::KHz;
    mUnitStringMap["MHz"] = Size::MHz;
    mUnitStringMap["GHz"] = Size::GHz;
    mUnitStringMap["Unknown"] = Size::Unknown;
    mUnitStringReverseMap[Size::GB] = "GB";
    mUnitStringReverseMap[Size::MB] = "MB";
    mUnitStringReverseMap[Size::KB] = "KB";
    mUnitStringReverseMap[Size::TB] = "TB";
    mUnitStringReverseMap[Size::B] = "B";
    mUnitStringReverseMap[Size::Hz] = "Hz";
    mUnitStringReverseMap[Size::KHz] = "KHz";
    mUnitStringReverseMap[Size::MHz] = "MHz";
    mUnitStringReverseMap[Size::GHz] = "GHz";
    mUnitStringReverseMap[Size::Unknown] = "Unknown";
}
void Size::convertTo(Unit u)
{
    if ((u == Size::Unknown) || (mUnit == Size::Unknown)) 
        return;

    double conversionFactor = 1024;
    if (u >= Size::Hz) {
        conversionFactor = 1000;
    }
    int diff = u - mUnit;
    if (diff > 0) {
        mValue /= pow(conversionFactor, diff);
    } else if (diff < 0) {
        mValue *= pow(conversionFactor, abs(diff));
    }
}

Size Size::operator+(Size op2)
{
    Size temp;
    temp.mValue = mValue;
    temp.mUnit = mUnit;
    op2.convertTo(mUnit);
    temp.mValue += op2.mValue;
    return temp;
}

std::ostream& operator<<(std::ostream& stream, Size& s)
{
    if (s.mUnit == Size::Unknown)
        stream << "";
    else 
        stream << s.mValue;
    return stream;
}
