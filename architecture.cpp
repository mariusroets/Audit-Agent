
#include <iostream>
#include <vector>
#include <string>
#include "architecture.h"
#include "commandparser.h"

Architecture *ARCH;

Architecture::Architecture()
{
    init();
}
Architecture::OSType Architecture::osType()
{
    return mOsType;
}

void Architecture::init()
{
    cout << "Architecture initialize ...\n";
    CommandParser c;
    vector<string> lines = c.parse("uname -s");
    if (lines.size() < 1) {
        // Bad error
        return;
    }
    if (lines[0] == "Linux") {
        mOsType = Linux;
    } else if (lines[0] == "Darwin") {
        mOsType = Darwin;
    } else {
        mOsType = Unknown;
    }
}
