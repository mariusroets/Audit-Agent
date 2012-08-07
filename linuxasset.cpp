
#include <vector>
#include "commandparser.h"
#include "linuxasset.h"
#include "util.h"

LinuxAsset::LinuxAsset()
{
}
LinuxAsset::~LinuxAsset()
{
}
void LinuxAsset::read()
{
    CommandParser parser;
    std::vector<std::string> lines = parser.parse("hostname");
    std::vector<std::vector<std::string> > fields = parser.split(".");
    mScanComp = "4.1.0.13";
    mMachineName = fields[0][0];
    mUniqueId = Util::SETTINGS->unique_id;
    lines = parser.parse("whoami");
    mUser = lines[0];
}
