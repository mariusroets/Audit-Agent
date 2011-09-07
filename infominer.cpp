#include <iostream>
#include <fstream>
#include <vector>

#include "infominer.h"
#include "cpu.h"
#include "os.h"
#include "memory.h"
#include "harddrive.h"
#include "system.h"
#include "network.h"
#include "software.h"
#include "asset.h"


InfoMiner::InfoMiner()
{
}
InfoMiner::~InfoMiner()
{
}
std::ostream& operator<<(std::ostream& stream, InfoMiner& im)
{
    vector<Info*> info;
    info.push_back(new Asset);
    info.push_back(new CPU);
    info.push_back(new OS);
    info.push_back(new Memory);
    info.push_back(new HardDrive);
    info.push_back(new System);
    info.push_back(new Software);
    info.push_back(new Network);

    for (int i = 0; i < (int)info.size(); i++) {
        stream << info[i]->output() << endl;
        delete info[i];
    }

    return stream;
}

