#include <iostream>
#include <fstream>

#include "infominer.h"
#include "cpu.h"
#include "os.h"
#include "memory.h"


InfoMiner::InfoMiner()
{
    CPU c;
    OS os;
    Memory mem;
    std::cout << c << std::endl << os << std::endl << mem;
}
InfoMiner::~InfoMiner()
{
}

