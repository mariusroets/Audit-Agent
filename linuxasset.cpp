
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
    CommandParser *parser = CommandParser::Instance();
    parser->parse("hostname");
    std::vector<std::string> lines = parser->lines();
    parser->split(".");
    std::vector<std::vector<std::string> > fields = parser->fields();
    mScanComp = Util::SETTINGS->scan_comp;
    mMachineName = fields[0][0];
    mUniqueId = Util::SETTINGS->unique_id;
    parser->parse("whoami");
    lines = parser->lines();
    mUser = lines[0];
}
