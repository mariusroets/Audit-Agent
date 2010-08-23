#include <iostream>
#include <fstream>

#include "infominer.h"
#include "cpu.h"
#include "os.h"


InfoMiner::InfoMiner()
{
    CPU c;
    OS os;
    std::cout << c << std::endl << os;
}
InfoMiner::~InfoMiner()
{
}

