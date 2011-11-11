/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __SOFTWARE_H__
#define __SOFTWARE_H__

#include <iostream>
#include <vector>
#include "info.h"
#include "size.h"

class Software : public Info
{
    public:
        struct SoftwarePackage {
            string name;
            string version;
            Size size;
            string install_time;
            string product_key;
            string product_nr;
        };
        Software();
        ~Software();
        std::string output();

    protected:
        vector<SoftwarePackage> mSoftwareList;

};

#endif	// __SOFTWARE_H__

