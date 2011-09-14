

#include "system.h"
#include "dmiparser.h"
#include "util.h"

System::System()
{
}
System::~System()
{
}

std::string System::output()
{
    stringstream stream;
    stream << "Manufacturer Name=" << mManufacturer << endl;
    stream << "Manufacturer Model=" << mManufacturerModel << endl;
    stream << "Manufacturer Version=" << mManufacturerVersion << endl;
    stream << "Manufacturer Serial=" << mManufacturerSerial << endl;
    stream << "Manufacturer UUID=" << mManufacturerUUID << endl << endl;
    stream << "Motherboard Make=" << mMotherBoardMake << endl;
    stream << "Motherboard Model=" << mMotherBoardModel << endl;
    stream << "Motherboard Version=" << mMotherBoardVersion << endl;
    stream << "Motherboard Serial=" << mMotherBoardSerial << endl << endl;
    stream << "Chassis Make=" << mChassisMake << endl;
    stream << "Chassis Model=" << mChassisModel << endl;
    stream << "Chassis Version=" << mChassisVersion << endl;
    stream << "Chassis Serial=" << mChassisSerial << endl;
    stream << "Chassis Asset Tag=" << mChassisAssetTag << endl << endl;
    stream << "BIOS Name=" << mBiosName << endl;
    stream << "BIOS Date=" << mBiosDate << endl;
    stream << "BIOS Version=" << mBiosVersion << endl;
    return stream.str();
}
std::ostream& operator<<(std::ostream& stream, System& sys)
{
    stream << sys.output();
    return stream;
}
