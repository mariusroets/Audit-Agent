
#include "monitor.h"

Monitor::Monitor()
{
}
Monitor::~Monitor()
{
}
std::string Monitor::output()
{
    stringstream stream;

    stream << "Monitor Count=" << mMonitors.size() << endl;
    for (int i = 0; i < (int)mMonitors.size(); i++) {
        stream << "Monitor" << i+1 << "=" << mMonitors[i].name << endl;
        stream << "Monitor Desc" << i+1 << "=" << mMonitors[i].description << endl;
        stream << "Monitor Manufacturer" << i+1 << "=" << mMonitors[i].manufacturer << endl;
        stream << "Monitor EDID Desc" << i+1 << "=" << mMonitors[i].edid << endl;
        stream << "Monitor Serial" << i+1 << "=" << mMonitors[i].serial << endl;
        stream << "Monitor Size" << i+1 << "=" << mMonitors[i].size << endl;
        stream << "Monitor Suffix" << i+1 << "=" << mMonitors[i].suffix << endl;
    }

    return stream.str();
}
void Monitor::read()
{
}
