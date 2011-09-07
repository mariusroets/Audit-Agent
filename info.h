/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __INFO_H__
#define __INFO_H__

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Info
{
    public:
        Info() {};
        virtual ~Info() {};
        virtual std::string output() =0;

    protected:
        virtual void read() =0;


};

#endif	// __INFO_H__
