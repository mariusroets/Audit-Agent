#include "info.h"
#include "architecture.h"
#include "linuxnetwork.h"
#include "macnetwork.h"

Info* Info::Factory(InfoType type)
{
    Architecture::OSType os = ARCH->osType();

    switch (type) {
        case Software:
            break;
        case Asset:
            break;
        case CPU:
            break;
        case Memory:
            break;
        case HardDrive:
            break;
        case System:
            break;
        case Network:
            if (os == Architecture::Linux) {
                return new LinuxNetwork();
            } else if (os == Architecture::Darwin) {
                return new MacNetwork();
            }
            break;
        default :
            // We don't know what to do, return null pointer
            return 0;
    }
    // We don't know what to do, return null pointer
    return 0;
}
