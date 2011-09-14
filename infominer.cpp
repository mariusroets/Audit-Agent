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
    info.push_back(Info::Factory(Info::Asset));
    info.push_back(Info::Factory(Info::CPU));
    info.push_back(Info::Factory(Info::OS));
    info.push_back(Info::Factory(Info::Memory));
    info.push_back(Info::Factory(Info::HardDrive));
    info.push_back(Info::Factory(Info::System));
    info.push_back(Info::Factory(Info::Software));
    info.push_back(Info::Factory(Info::Network));

    for (int i = 0; i < (int)info.size(); i++) {
        if (!info[i]) {
            cerr << "Skipping info " << i << ". Could not instantiate class" << endl;
            continue;
        }
        stream << info[i]->output() << endl;
        delete info[i];
    }

    return stream;
}

