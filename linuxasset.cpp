
#include <vector>
#include "commandparser.h"
#include "linuxasset.h"

LinuxAsset::LinuxAsset()
{
    read();
}
LinuxAsset::~LinuxAsset()
{
}
void LinuxAsset::read()
{
    CommandParser parser;
    std::vector<std::string> lines = parser.parse("hostname");
    std::vector<std::vector<std::string> > fields = parser.split(".");
    mMachineName = fields[0][0];
    lines = parser.parse("whoami");
    mUser = lines[0];
}
