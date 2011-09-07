
#include <vector>
#include "network.h"
#include "dmiparser.h"
#include "commandparser.h"
#include "util.h"

Network::Network()
{
    read();
}

Network::~Network()
{
}

std::string Network::output()
{
    stringstream stream;
    stream << mHardware << mLineEnding;
    for (int i = 0 ; i < (int)mAdapters.size(); i++) {
        stream << "Adapters" << i+1 << "=" << mAdapters[i].name << mLineEnding;
        stream << "Adapters Mac" << i+1 << "=" << mAdapters[i].mac << mLineEnding;
        stream << "Adapters IP" << i+1 << "=" << mAdapters[i].ip << mLineEnding;
        stream << "Adapters Cnt" << i+1 << "=" << mAdapters[i].count << mLineEnding;
        stream << "Adapters Suffix" << i+1 << "=" << mAdapters[i].suffix << mLineEnding;
        stream << "Adapters Subnet" << i+1 << "=" << mAdapters[i].mask << mLineEnding;
        
    }
    return stream.str();
}

void Network::read()
{
    mAdapters.clear();
    DMIParser parser(DMIParser::OnBoard);
    parser.exec();
    for (int i = 0; i < parser.frameCount(); ++i) {
        parser.setCurrentFrame(i);
        if (parser["Type"] == "Ethernet") {
            mHardware = parser["Description"];
        }
    }
    CommandParser cmdparser;
    std::vector<std::string> lines = cmdparser.parse("sudo /sbin/ifconfig");
    std::vector<std::vector<std::string> > fields = cmdparser.split(SPACES);
    bool in_adapter = false;
    int index = 0;
    for (int i = 0; i < (int)fields.size(); i++) {
        if (fields[i].size() <= 1)
            continue;
        if (fields[i][1] == "Link") {
            in_adapter = true;
            mAdapters.push_back(Adapter());
            index = mAdapters.size() - 1;
            mAdapters[index].name = fields[i][0];
            if (fields[i].size() >= 5)
                mAdapters[index].mac = fields[i][4];
            // Have no idea what this is, but it seems to be 1 always.
            mAdapters[index].count = 1;
        }
        if ((fields[i][0] == "inet") && in_adapter) {
            mAdapters[index].ip = fields[i][1];
            if (fields[i].size() >= 4)
                mAdapters[index].mask = fields[i][3];
        }

    }

}

std::ostream& operator<<(std::ostream& stream, Network& nw)
{
    stream << nw.output();
    return stream;
}
