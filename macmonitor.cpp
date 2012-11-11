
#include "macmonitor.h"
#include "sysprofileparser.h"


MacMonitor::MacMonitor()
{
}
MacMonitor::~MacMonitor()
{
}
void MacMonitor::read()
{
    SysProfileParser *sys = SysProfileParser::Instance();
    vector<string> cards = sys->children("Graphics/Displays");
    for (int i = 0; i < (int)cards.size(); i++) {
        vector<string> monitors = sys->children(string("Graphics/Displays:") + cards[i] + ":Displays");
        for (int j = 0; j < (int)monitors.size(); j++) {
            string status = sys->value(string("Graphics/Displays:") + cards[i] + ":Displays:" + monitors[j] + ":Status");
            if (status == "No Display Connected")
                continue;
            mMonitors.push_back(Screen());
            mMonitors[j].name = monitors[i];
            mMonitors[j].size = sys->value(string("Graphics/Displays:") + cards[i] + ":Displays:" + monitors[j] + ":Resolution");
        }
        
    }
}
