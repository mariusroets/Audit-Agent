
#include "software.h"

Software::Software()
{
}

Software::~Software()
{
}

std::string Software::output()
{

    stringstream stream;
    stream << "Hotfix Count=" << 0 << endl;
    stream << endl;
    stream << "Software Count=" << mSoftwareList.size() << endl;
    for (int i = 0; i < (int)mSoftwareList.size(); i++) {
        int count = i+1;
        stream << "Software" << count << "=" << mSoftwareList[i].name;
        stream << "|" << mSoftwareList[i].size;
        stream << "|" << mSoftwareList[i].install_time;
        stream << "|" << mSoftwareList[i].version;
        stream << "|" << mSoftwareList[i].product_key;
        stream << "|" << mSoftwareList[i].product_nr;
    }
    return stream.str();
}

