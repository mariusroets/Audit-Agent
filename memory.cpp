
#include "memory.h"


Memory::Memory()
{
    read();
}
void Memory::read()
{
}

std::ostream& operator<<(std::ostream& stream, Memory& mem)
{
    return stream;
}
