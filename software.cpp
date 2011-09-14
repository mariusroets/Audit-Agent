
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
    stream << "Software Count=" << 0 << endl;
    return stream.str();
}

