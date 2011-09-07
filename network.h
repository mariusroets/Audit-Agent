/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <iostream>
#include "info.h"

class Network : public Info
{
    public:
        struct Adapter {
            std::string name;
            std::string mac;
            std::string ip;
            std::string suffix;
            std::string mask;
            int count;
        };
        Network();
        ~Network();
        std::string output();

        friend std::ostream& operator<<(std::ostream& stream, Network& nw);
    protected:
        void read();

    private:
        std::string mHardware;
        std::vector<Adapter> mAdapters;


};

#endif	// __NETWORK_H__

