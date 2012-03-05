
#include <cstdlib>
#include "maccpu.h"
#include "sysprofileparser.h"

MacCPU::MacCPU()
{
}
MacCPU::~MacCPU()
{
}
void MacCPU::read()
{
    SysProfileParser sys;
    sys.parse();

    mCount = atoi(sys.value("Hardware:Hardware Overview:Number Of CPUs").c_str());
    mSpeed.set(sys.value("Hardware:Hardware Overview:Processor Speed"));
    mType = sys.value("Hardware:Hardware Overview:Processor Name");
    mIdString = sys.value("Hardware:Hardware Overview:Model Identifier");
    mSerial = sys.value("Hardware:Hardware Overview:Serial Number (system)");

}
