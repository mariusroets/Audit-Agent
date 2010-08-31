/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __SOFTWARE_H__
#define __SOFTWARE_H__

#include <iostream>
#include "info.h"

class Software : public Info
{
    public:
        Software();
        ~Software();

        friend std::ostream& operator<<(std::ostream& stream, Software& sw);
    protected:
        void read();


};

#endif	// __SOFTWARE_H__

