
#include <ctime>
#include "macsoftware.h"
#include "commandparser.h"
#include "util.h"

MacSoftware::MacSoftware()
{
}
MacSoftware::~MacSoftware()
{
}
void MacSoftware::read()
{
    Util::exec("pkgutil --package > /tmp/pkgutil.txt");
    CommandParser c;
    c.parse("cat", "/tmp/pkgutil.txt");
    vector<string> lines = c.lines();
    for (int i = 0; i < (int)lines.size(); i++) {
        mSoftwareList.push_back(SoftwarePackage());
        mSoftwareList[i].name = lines[i];
        CommandParser c2;
        c2.parse("pkgutil", "--pkg-info " + lines[i]);
        vector<string> lines2 = c2.lines();
        c2.split(":");
        vector<vector<string> > fields = c2.fields();
        for (int j = 0; j < (int)lines2.size(); j++) {
            if (fields[j][0] == "version") {
                mSoftwareList[i].version = fields[j][1];
            }
            if (fields[j][0] == "install-time") {
                //TODO: Format the time which is a time_t to a string
                // and poplulate mSoftwareList[i].install_time
                //mSoftwareList[i].install_time = fields[j][1];
            }
            
        }
    }
}
