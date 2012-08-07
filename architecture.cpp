
#include <iostream>
#include <vector>
#include <string>
#include "architecture.h"
#include "commandparser.h"
#include "util.h"

Architecture *ARCH;

Architecture::Architecture()
{
    mOsType = Unknown;
    init();
}
Architecture::OSType Architecture::osType()
{
    return mOsType;
}

void Architecture::init()
{
    string l;
    // Architecture can be forced from settings for testing
    l = Util::SETTINGS->architecture;

    // If not forced, determine architecture
    if (l.empty()) {
        CommandParser c;
        vector<string> lines = c.parse("uname -s");
        if (lines.size() < 1) {
            // Bad error
            return;
        }
        l = lines[0];
    }
    if (l == "Linux") {
        mOsType = Linux;
    } else if (l == "Darwin") {
        mOsType = Darwin;
    } else {
        mOsType = Unknown;
    }
}
