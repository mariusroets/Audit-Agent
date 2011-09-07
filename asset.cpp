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
    stream << "Machine Name=" << mMachineName << endl;
    stream << "Asset Number=" << mAssetNumber << endl;
    stream << "Generated Unique ID=" << mUniqueId<< endl;
    stream << "Scancomp=" << mScanComp << endl;
    stream << "User Name=" << mUser << endl;
    stream << "NW User Name=" << mNWUser<< endl;
    stream << "PC Description=" << mDescription << endl;

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

