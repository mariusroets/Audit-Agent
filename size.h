/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __SIZE_H__
#define __SIZE_H__

#include <string>
#include <map>

using namespace std;

class Size
{
    public:
        enum Unit { Unknown, KB , MB , GB , TB };
        Size();
        Size(const string& s);

        friend std::ostream& operator<<(std::ostream& stream, Size& s);

    private:
        double mValue;
        Unit mUnit;
        map<string, Unit> mUnitStringMap;
        map<Unit, string> mUnitStringReverseMap;


        Unit determineUnit(const string& u);
        void init();
};

#endif	// __SIZE_H__

