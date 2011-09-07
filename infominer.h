/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __INFOMINER_H__
#define __INFOMINER_H__

#include <string>

using namespace std;

class InfoMiner
{
    public:
        InfoMiner();
        ~InfoMiner();

        friend std::ostream& operator<<(std::ostream& stream, InfoMiner& im);

};

#endif	// __INFOMINER_H__


