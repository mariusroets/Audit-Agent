#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "commandparser.h"
#include "asset.h"


Asset::Asset()
{
    read();
}
Asset::~Asset()
{
}

std::string Asset::output()
{
    stringstream stream;
    stream << "Machine Name=" << mMachineName << mLineEnding;
    stream << "Asset Number=" << mAssetNumber << mLineEnding;
    stream << "Generated Unique ID=" << mUniqueId<< mLineEnding;
    stream << "Scancomp=" << mScanComp << mLineEnding;
    stream << "User Name=" << mUser << mLineEnding;
    stream << "NW User Name=" << mNWUser<< mLineEnding;
    stream << "PC Description=" << mDescription << mLineEnding;

    return stream.str();
}
void Asset::read()
{
    CommandParser parser;
    std::vector<std::string> lines = parser.parse("hostname");
    std::vector<std::vector<std::string> > fields = parser.split(".");
    mMachineName = fields[0][0];
    lines = parser.parse("whoami");
    mUser = lines[0];

	
}
std::ostream& operator<<(std::ostream& stream, Asset& asset) 
{
    stream << asset.output();
    return stream;
}

