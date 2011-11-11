/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __MONITOR_H__
#define __MONITOR_H__

#include <vector>
#include "info.h"

class Monitor : public Info
{
    public:
        struct Screen {
            Screen() {
                name = "";
                description = "";
                manufacturer = "";
                edid = "";
                serial = "";
                size = "";
                suffix = 0;
            }
                    
            std::string name;
            std::string description;
            std::string manufacturer;
            std::string edid;
            std::string serial;
            std::string size;
            int suffix;
        };
        Monitor();
        ~Monitor();
        string output();

    protected:
        vector<Screen> mMonitors;

        virtual void read();
};

#endif	// __MONITOR_H__

