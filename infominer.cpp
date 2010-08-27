#include <iostream>
#include <fstream>

#include "infominer.h"
#include "cpu.h"
#include "os.h"
#include "memory.h"
#include "harddrive.h"


InfoMiner::InfoMiner()
{
    CPU c;
    OS os;
    Memory mem;
    HardDrive hd;
    std::cout << c << std::endl << os << std::endl << mem << std::endl << hd;
}
InfoMiner::~InfoMiner()
{
}

