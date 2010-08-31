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
        Network();
        ~Network();

        friend std::ostream& operator<<(std::ostream& stream, Network& nw);
    protected:
        void read();

    private:
        std::string mHardware;


};

#endif	// __NETWORK_H__

