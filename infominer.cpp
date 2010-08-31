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
    CPU c;
    OS os;
    Memory mem;
    HardDrive hd;
    System sys;
    Software sw;
    Network nw;
    std::cout << c << std::endl;
    std::cout << os << std::endl;
    std::cout << mem << std::endl;
    std::cout << hd << std::endl;
    std::cout << sys << std::endl;
    std::cout << nw << std::endl;
    std::cout << sw << std::endl;
}
InfoMiner::~InfoMiner()
{
}

