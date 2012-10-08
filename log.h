/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/


#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <map>
#include "logfile.h"

/**
 * Monoid pattern to implement a log file singleton
 */
class Log
{
    public:
        static LogFile* Instance(); 

    private:
        static void cleanUp();

        Log(); 
        ~Log() {}

        // not copyable
        Log(Log const&);
        Log& operator=(Log const&);

        static LogFile* mInstance;
};

#endif	// __LOG_H__


