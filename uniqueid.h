/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __UNIQUEID_H__
#define __UNIQUEID_H__

#include <string>

class UniqueId
{
    public:
        UniqueId();
        ~UniqueId();
        
        std::string id();


    private:
        std::string unique;

        void generate();
        void write();
        void read();
};

#endif	// __UNIQUEID_H__

