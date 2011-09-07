
#include "network.h"
#include "dmiparser.h"

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
    return stream.str();
}

void Network::read()
{
    DMIParser parser(DMIParser::OnBoard);
    parser.exec();
    for (int i = 0; i < parser.frameCount(); ++i) {
        parser.setCurrentFrame(i);
        if (parser["Type"] == "Ethernet") {
            mHardware = parser["Description"];
        }
    }
}

std::ostream& operator<<(std::ostream& stream, Network& nw)
{
    stream << nw.output();
    return stream;
}
