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
#include "util.h"
#include "log.h"


InfoMiner::InfoMiner()
{
}
InfoMiner::~InfoMiner()
{
}
std::ostream& operator<<(std::ostream& stream, InfoMiner& im)
{
    vector<Info*> info;
    LogFile* l = Log::Instance();
    l->writeLine("Initializing Information Collectors");
    info.push_back(Info::Factory(Info::Asset));
    info.push_back(Info::Factory(Info::CPU));
    info.push_back(Info::Factory(Info::OS));
    info.push_back(Info::Factory(Info::Memory));
    info.push_back(Info::Factory(Info::HardDrive));
    info.push_back(Info::Factory(Info::System));
    if (Util::SETTINGS->all_software) {
        info.push_back(Info::Factory(Info::Software));
    }
    info.push_back(Info::Factory(Info::Monitor));
    info.push_back(Info::Factory(Info::Network));

    for (int i = 0; i < (int)info.size(); i++) {
        if (!info[i]) {
            cerr << "Skipping info " << i << ". Could not instantiate class" << endl;
            continue;
        }
        l->writeDebug("   Information collection for " + info[i]->name());
        info[i]->read();
        l->writeDebug("   Information writing for " + info[i]->name());
        stream << info[i]->output() << endl;
        l->writeDebug("   Deleting collector " + info[i]->name());
        delete info[i];
    }

    return stream;
}

