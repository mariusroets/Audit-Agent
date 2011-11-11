
#include "macsoftware.h"
#include "commandparser.h"

MacSoftware::MacSoftware()
{
}
MacSoftware::~MacSoftware()
{
}
void MacSoftware::read()
{
    CommandParser c;
    vector<string> lines = c.parse("cat pkgutil.txt");
    for (int i = 0; i < (int)lines.size(); i++) {
        mSoftwareList.push_back(SoftwarePackage());
        mSoftwareList[i].name = lines[i];
        CommandParser c2;
        vector<string> lines2 = c2.parse(string("pkgutil --pkg-info ") + lines[i]);
        vector<vector<string> > fields = c2.split(":");
        for (int j = 0; j < (int)lines2.size(); j++) {
            if (fields[j][0] == "version") {
                mSoftwareList[i].version = fields[j][1];
            }
            if (fields[j][0] == "install-time") {
                mSoftwareList[i].install_time = fields[j][1];
            }
            
        }
    }
}
