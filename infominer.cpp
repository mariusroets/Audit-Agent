#include <iostream>
#include <fstream>

#include "infominer.h"
#include "cpu.h"
#include "os.h"
#include "memory.h"
#include "harddrive.h"
#include "system.h"


InfoMiner::InfoMiner()
{
    CPU c;
    OS os;
    Memory mem;
    HardDrive hd;
    System sys;
    std::cout << c << std::endl;
    std::cout << os << std::endl;
    std::cout << mem << std::endl;
    std::cout << hd << std::endl;
    std::cout << sys << std::endl;
}
InfoMiner::~InfoMiner()
{
}

