
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
    cmdparser->parse("rpm", "--queryformat '%{NAME}#%{VERSION}#%{INSTALLTIME:date}#%{SIZE}\\n' -qa", true);
    std::vector<std::string> lines = cmdparser->lines();
    cmdparser->split("#");
    std::vector<std::vector<std::string> > fields = cmdparser->fields();

    int count = -1;
    for (int i = 0; i < (int)fields.size(); i++) {
        if (fields[i].size() <= 1)
            continue;
        if (!fields[i][0].empty()) {
            count++;
            mSoftwareList.push_back(SoftwarePackage());
            mSoftwareList[count].name = fields[i][0];
        }
        if (!fields[i][1].empty()) {
            mSoftwareList[count].version = fields[i][1];
        }
        if (!fields[i][2].empty()) {
            mSoftwareList[count].install_time = fields[i][2];
        }
        if (!fields[i][3].empty()) {
            mSoftwareList[count].size = Size(fields[i][3]+"B");
            mSoftwareList[count].size.convertTo(Size::KB);
        }
    }
}
