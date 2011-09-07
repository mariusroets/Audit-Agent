
#include "software.h"

Software::Software()
{
    read();
}

Software::~Software()
{
}

std::string Software::output()
{
    stringstream stream;
    stream << "Hotfix Count=" << 0 << mLineEnding;
    stream << mLineEnding;
    stream << "Software Count=" << 0 << mLineEnding;
    return stream.str();
}

void Software::read()
{
}

std::ostream& operator<<(std::ostream& stream, Software& sw)
{
    stream << sw.output();
    return stream;
}
