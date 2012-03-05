#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

#include "commandparser.h"
#include "asset.h"


Asset::Asset()
{
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

