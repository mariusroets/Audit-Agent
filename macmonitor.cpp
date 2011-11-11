
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
    vector<string> cards = SYS->children("Graphics/Displays");
    for (int i = 0; i < (int)cards.size(); i++) {
        vector<string> monitors = SYS->children(string("Graphics/Displays:") + cards[i] + ":Displays");
        for (int j = 0; j < (int)monitors.size(); j++) {
            string status = SYS->value(string("Graphics/Displays:") + cards[i] + ":Displays:" + monitors[j] + ":Status");
            if (status == "No Display Connected")
                continue;
            mMonitors.push_back(Screen());
            mMonitors[j].name = monitors[i];
            mMonitors[j].size = SYS->value(string("Graphics/Displays:") + cards[i] + ":Displays:" + monitors[j] + ":Resolution");
        }
        
    }
}
