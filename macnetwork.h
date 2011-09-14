/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#include "network.h"

#ifndef __MACNETWORK_H__
#define __MACNETWORK_H__

class MacNetwork : public Network
{
    public:
        MacNetwork();
        ~MacNetwork();
    protected:
        void read();

};

#endif	// __MACNETWORK_H__

