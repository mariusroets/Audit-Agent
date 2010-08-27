/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <ostream>
#include "info.h"

class System : public Info
{
    public:
        System();
        ~System();

        friend std::ostream& operator<<(std::ostream& stream, System& sys);
    protected:
        void read();


    private:
        std::string mManufacturer;
        std::string mManufacturerModel;
        std::string mManufacturerVersion;
        std::string mManufacturerSerial;
        std::string mManufacturerUUID;
        std::string mMotherBoardMake;
        std::string mMotherBoardModel;
        std::string mMotherBoardVersion;
        std::string mMotherBoardSerial;
        std::string mChassisMake;
        std::string mChassisModel;
        std::string mChassisVersion;
        std::string mChassisSerial;
        std::string mChassisAssetTag;
        std::string mBiosName;
        std::string mBiosVersion;
        std::string mBiosDate;

};

#endif	// __SYSTEM_H__

