/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <iostream>
#include <vector>
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

        static Network* Factory();

        friend std::ostream& operator<<(std::ostream& stream, Network& nw);

    protected:
        std::string mHardware;
        std::vector<Adapter> mAdapters;

        virtual void read();


};

#endif	// __NETWORK_H__

