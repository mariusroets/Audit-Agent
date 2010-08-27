

#include "system.h"
#include "dmiparser.h"
#include "util.h"

System::System()
{
    read();
}
System::~System()
{
}

void System::read()
{
    DMIParser p1(DMIParser::System);
    DMIParser p2(DMIParser::MotherBoard);
    DMIParser p3(DMIParser::Chassis);
    DMIParser p4(DMIParser::Bios);
    p1.exec();
    p2.exec();
    p3.exec();
    p4.exec();
    p1.setCurrentFrame(0);
    p2.setCurrentFrame(0);
    p3.setCurrentFrame(0);
    p4.setCurrentFrame(0);

    mManufacturer = p1["Manufacturer"];
    mManufacturerModel = p1["Product Name"];
    mManufacturerVersion = p1["Version"];
    mManufacturerSerial = p1["Serial Number"];
    mManufacturerUUID = p1["UUID"];
    mMotherBoardMake = p2["Manufacturer"];
    mMotherBoardModel = p2["Product Name"];
    mMotherBoardVersion = p2["Version"];
    mMotherBoardSerial = p2["Serial Number"];
    mChassisMake = p3["Manufacturer"];
    mChassisModel = p3["Type"];
    mChassisVersion = p3["Version"];
    mChassisSerial = p3["Serial Number"];
    mChassisAssetTag = p3["Asset Tag"];
    mBiosName = p4["Vendor"];
    mBiosVersion = p4["Version"];
    mBiosDate = p4["Release Date"];


}
std::ostream& operator<<(std::ostream& stream, System& sys)
{
    stream << "Manufacturer Name=" << sys.mManufacturer << std::endl;
    stream << "Manufacturer Model=" << sys.mManufacturerModel << std::endl;
    stream << "Manufacturer Version=" << sys.mManufacturerVersion << std::endl;
    stream << "Manufacturer Serial=" << sys.mManufacturerSerial << std::endl;
    stream << "Manufacturer UUID=" << sys.mManufacturerUUID << std::endl << std::endl;
    stream << "Motherboard Make=" << sys.mMotherBoardMake << std::endl;
    stream << "Motherboard Model=" << sys.mMotherBoardModel << std::endl;
    stream << "Motherboard Version=" << sys.mMotherBoardVersion << std::endl;
    stream << "Motherboard Serial=" << sys.mMotherBoardSerial << std::endl << std::endl;
    stream << "Chassis Make=" << sys.mChassisMake << std::endl;
    stream << "Chassis Model=" << sys.mChassisModel << std::endl;
    stream << "Chassis Version=" << sys.mChassisVersion << std::endl;
    stream << "Chassis Serial=" << sys.mChassisSerial << std::endl;
    stream << "Chassis Asset Tag=" << sys.mChassisAssetTag << std::endl << std::endl;
    stream << "BIOS Name=" << sys.mBiosName << std::endl;
    stream << "BIOS Date=" << sys.mBiosDate << std::endl;
    stream << "BIOS Version=" << sys.mBiosVersion << std::endl;
    return stream;
}
