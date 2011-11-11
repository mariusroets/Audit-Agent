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
        enum InfoType { Software, Asset, CPU, OS, Memory, HardDrive, System, Network };
        Info() {};
        virtual ~Info() {};
        virtual std::string output() =0;

        static Info* Factory(InfoType type);
        virtual void read() =0;


};

#endif	// __INFO_H__
