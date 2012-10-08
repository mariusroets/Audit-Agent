#include "info.h"
#include "architecture.h"
#include "linuxnetwork.h"
#include "macnetwork.h"
#include "linuxasset.h"
#include "macasset.h"
#include "linuxcpu.h"
#include "maccpu.h"
#include "linuxharddrive.h"
#include "macharddrive.h"
#include "linuxmemory.h"
#include "macmemory.h"
#include "linuxos.h"
#include "macos.h"
#include "linuxsoftware.h"
#include "macsoftware.h"
#include "linuxsystem.h"
#include "macsystem.h"
#include "macmonitor.h"
#include "linuxmonitor.h"
#include "log.h"

Info::Info()
{
    // Initialize in the same order as InfoType enum
    mNameMap.push_back("Software");
    mNameMap.push_back("Asset");
    mNameMap.push_back("CPU");
    mNameMap.push_back("OS");
    mNameMap.push_back("Memory");
    mNameMap.push_back("HardDrive");
    mNameMap.push_back("System");
    mNameMap.push_back("Network");
    mNameMap.push_back("Monitor");
    mLog = Log::Instance();

}
void Info::writeInitLogMessage()
{
    mLog->writeDebug("   Collector Initialized : " + name());
}
Info* Info::Factory(InfoType type)
{
    Architecture::OSType os = ARCH->osType();
    Info *i = 0;

    switch (type) {
        case Software:
            if (os == Architecture::Linux) {
                return new LinuxSoftware();
            } else if (os == Architecture::Darwin) {
                i = new MacSoftware();
            }
            break;
        case OS:
            if (os == Architecture::Linux) {
                i = new LinuxOS();
            } else if (os == Architecture::Darwin) {
                i = new MacOS();
            }
            break;
        case Asset:
            if (os == Architecture::Linux) {
                i = new LinuxAsset();
            } else if (os == Architecture::Darwin) {
                i = new MacAsset();
            }
            break;
        case CPU:
            if (os == Architecture::Linux) {
                i = new LinuxCPU();
            } else if (os == Architecture::Darwin) {
                i = new MacCPU();
            }
            break;
        case Memory:
            if (os == Architecture::Linux) {
                i = new LinuxMemory();
            } else if (os == Architecture::Darwin) {
                i = new MacMemory();
            }
            break;
        case HardDrive:
            if (os == Architecture::Linux) {
                i = new LinuxHardDrive();
            } else if (os == Architecture::Darwin) {
                i = new MacHardDrive();
            }
            break;
        case System:
            if (os == Architecture::Linux) {
                i = new LinuxSystem();
            } else if (os == Architecture::Darwin) {
                i = new MacSystem();
            }
            break;
        case Network:
            if (os == Architecture::Linux) {
                i = new LinuxNetwork();
            } else if (os == Architecture::Darwin) {
                i = new MacNetwork();
            }
            break;
        case Monitor:
            if (os == Architecture::Linux) {
                i = new LinuxMonitor();
            } else if (os == Architecture::Darwin) {
                i = new MacMonitor();
            }
            break;
        default :
            // We don't know what to do, return null pointer
            return 0;

    }
    i->writeInitLogMessage();
    return i;
}
std::string Info::name() const
{
    if ((mInfoType >= 0) && (mInfoType < mNameMap.size())) {
        return mNameMap[mInfoType];
    }
    return "Undefined";
}
