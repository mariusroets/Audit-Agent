#include <iostream>
#include <fstream>

#include "infominer.h"
#include "cpu.h"
#include "os.h"
#include "memory.h"
#include "harddrive.h"
#include "system.h"
#include "network.h"
#include "software.h"


InfoMiner::InfoMiner()
{
}
InfoMiner::~InfoMiner()
{
}
std::ostream& operator<<(std::ostream& stream, InfoMiner& im)
{
    CPU c;
    OS os;
    Memory mem;
    HardDrive hd;
    System sys;
    Software sw;
    Network nw;
    stream << c << std::endl;
    stream << os << std::endl;
    stream << mem << std::endl;
    stream << hd << std::endl;
    stream << sys << std::endl;
    stream << nw << std::endl;
    stream << sw << std::endl;

    return stream;
}

