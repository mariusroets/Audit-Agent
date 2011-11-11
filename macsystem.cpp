
#include "macsystem.h"
#include "dmiparser.h"
#include "sysprofileparser.h"

MacSystem::MacSystem()
{
    read();
}
MacSystem::~MacSystem()
{
}
void MacSystem::read()
{

    mManufacturer = "Apple";
    mManufacturerModel = SYS->value("Hardware:Hardware Overview:Model Name");
    mManufacturerVersion = SYS->value("Hardware:Hardware Overview:Model Name");
    mManufacturerSerial = SYS->value("Hardware:Hardware Overview:Serial Number (system)");
    mManufacturerUUID = SYS->value("Hardware:Hardware Overview:Hardware UUID");
    mMotherBoardMake = "";
    mMotherBoardModel = "";
    mMotherBoardVersion = "";
    mMotherBoardSerial = "";
    mChassisMake = "Apple";
    mChassisModel = SYS->value("Hardware:Hardware Overview:Model Name");
    mChassisVersion = "";
    mChassisSerial = "";
    mChassisAssetTag = "";
    mBiosName = "";
    mBiosVersion =SYS->value("Hardware:Hardware Overview:Boot ROM Version");
    mBiosDate = "";
}
