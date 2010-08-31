
#include "software.h"

Software::Software()
{
    read();
}

Software::~Software()
{
}

void Software::read()
{
}

std::ostream& operator<<(std::ostream& stream, Software& sw)
{
    stream << "Hotfix Count=" << 0 << std::endl;
    stream << std::endl;
    stream << "Software Count=" << 0 << std::endl;
    return stream;
}
