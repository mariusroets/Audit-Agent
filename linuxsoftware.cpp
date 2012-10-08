
#include "linuxsoftware.h"
#include "commandparser.h"
#include "util.h"

LinuxSoftware::LinuxSoftware()
{
}
LinuxSoftware::~LinuxSoftware()
{
}
void LinuxSoftware::read()
{
    CommandParser *cmdparser = CommandParser::Instance();
    cmdparser->parse("rpm", "-qai", true);
    std::vector<std::string> lines = cmdparser->lines();
    cmdparser->split(":");
    std::vector<std::vector<std::string> > fields = cmdparser->fields();

    int count = -1;
    for (int i = 0; i < (int)fields.size(); i++) {
        if (fields[i].size() <= 1)
            continue;
        if (fields[i][0] == "Name") {
            count++;
            mSoftwareList.push_back(SoftwarePackage());
            mSoftwareList[count].name = fields[i][1];
        }
        if (fields[i][0] == "Version") {
            mSoftwareList[count].version = fields[i][1];
        }
        if (fields[i][0] == "Install Date") {
            mSoftwareList[count].install_time = fields[i][1];
        }
        if (fields[i][0] == "Size") {
            mSoftwareList[count].size = Size(fields[i][1]+"B");
            mSoftwareList[count].size.convertTo(Size::KB);

        }

    }
}
