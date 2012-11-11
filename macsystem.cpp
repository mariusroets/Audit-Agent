
#include "macsystem.h"
#include "dmiparser.h"
#include "sysprofileparser.h"

MacSystem::MacSystem()
{
}
MacSystem::~MacSystem()
{
}
void MacSystem::read()
{
    SysProfileParser *sys = SysProfileParser::Instance();

    mManufacturer = "Apple";
    mManufacturerModel = sys->value("Hardware:Hardware Overview:Model Name");
    mManufacturerVersion = sys->value("Hardware:Hardware Overview:Model Name");
    mManufacturerSerial = sys->value("Hardware:Hardware Overview:Serial Number (system)");
    mManufacturerUUID = sys->value("Hardware:Hardware Overview:Hardware UUID");
    mMotherBoardMake = "";
    mMotherBoardModel = "";
    mMotherBoardVersion = "";
    mMotherBoardSerial = "";
    mChassisMake = "Apple";
    mChassisModel = sys->value("Hardware:Hardware Overview:Model Name");
    mChassisVersion = "";
    mChassisSerial = "";
    mChassisAssetTag = "";
    mBiosName = "";
    mBiosVersion = sys->value("Hardware:Hardware Overview:Boot ROM Version");
    mBiosDate = "";
}
