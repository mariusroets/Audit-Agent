/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __OS_H__
#define __OS_H__

#include <ostream>
#include <string>
#include "info.h"

class OS : public Info
{
    public:
        OS();
        ~OS();
        std::string output();

        friend std::ostream& operator<<(std::ostream& stream, OS& os);

    protected:
        std::string mName;
        std::string mMajorVersion;
        std::string mMinorVersion;
        std::string mBuild;
        std::string mServicePack;
        std::string mProductId;
        std::string mProductNo;
};

#endif	// __OS_H__

