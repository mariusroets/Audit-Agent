
#include <cstdlib>
#include "log.h"

LogFile* Log::mInstance = 0;

LogFile* Log::Instance()
{
    if (!mInstance) {
        mInstance = new LogFile();
        atexit(&cleanUp);
    }
    return mInstance;
}
Log::Log()
{
}
void Log::cleanUp()
{
    if (mInstance)
        delete mInstance;
    mInstance = 0;
}
