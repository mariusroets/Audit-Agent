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


InfoMiner::InfoMiner()
{
    mLineEnding = "\n";
}
InfoMiner::~InfoMiner()
{
}
void InfoMiner::setLineEnding(const std::string& le)
{
    mLineEnding = le;
}
std::ostream& operator<<(std::ostream& stream, InfoMiner& im)
{
    vector<Info*> info;
    info.push_back(new CPU);
    info.push_back(new OS);
    info.push_back(new Memory);
    info.push_back(new HardDrive);
    info.push_back(new System);
    info.push_back(new Software);
    info.push_back(new Network);

    for (int i = 0; i < (int)info.size(); i++) {
        info[i]->setLineEnding(im.mLineEnding);
        stream << info[i]->output() << im.mLineEnding;
        delete info[i];
    }

    return stream;
}

