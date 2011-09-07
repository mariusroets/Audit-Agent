

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

std::string System::output()
{
    stringstream stream;
    stream << "Manufacturer Name=" << mManufacturer << mLineEnding;
    stream << "Manufacturer Model=" << mManufacturerModel << mLineEnding;
    stream << "Manufacturer Version=" << mManufacturerVersion << mLineEnding;
    stream << "Manufacturer Serial=" << mManufacturerSerial << mLineEnding;
    stream << "Manufacturer UUID=" << mManufacturerUUID << mLineEnding << mLineEnding;
    stream << "Motherboard Make=" << mMotherBoardMake << mLineEnding;
    stream << "Motherboard Model=" << mMotherBoardModel << mLineEnding;
    stream << "Motherboard Version=" << mMotherBoardVersion << mLineEnding;
    stream << "Motherboard Serial=" << mMotherBoardSerial << mLineEnding << mLineEnding;
    stream << "Chassis Make=" << mChassisMake << mLineEnding;
    stream << "Chassis Model=" << mChassisModel << mLineEnding;
    stream << "Chassis Version=" << mChassisVersion << mLineEnding;
    stream << "Chassis Serial=" << mChassisSerial << mLineEnding;
    stream << "Chassis Asset Tag=" << mChassisAssetTag << mLineEnding << mLineEnding;
    stream << "BIOS Name=" << mBiosName << mLineEnding;
    stream << "BIOS Date=" << mBiosDate << mLineEnding;
    stream << "BIOS Version=" << mBiosVersion << mLineEnding;
    return stream.str();
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
    stream << sys.output();
    return stream;
}
