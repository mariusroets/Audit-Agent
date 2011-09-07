/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __ARCHITECTURE_H__
#define __ARCHITECTURE_H__

using namespace std;
/**
 * Contains information about the architecture that we are
 * working on. All architecture information, including OS,
 * and version number should go in here. It should be populated
 * at program initialization. Other code then makes decisions
 * based on the state of the object.
 */
class Architecture
{
    public:
        enum OSType { Unknown, Linux, Darwin };
        Architecture();
        OSType osType();

    private:
        OSType mOsType;

        void init();

};

#endif	// __ARCHITECTURE_H__

