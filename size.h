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
        enum Unit { Unknown, B, KB , MB , GB , TB };
        Size();
        Size(const Size& s);
        Size(const string& s);
        void set(const string& s);
        void convertTo(Unit u);

        Size operator+(Size op2);

        friend std::ostream& operator<<(std::ostream& stream, Size& s);

    private:
        double mValue;
        Unit mUnit;
        map<string, Unit> mUnitStringMap;
        map<Unit, string> mUnitStringReverseMap;


        Unit determineUnit(const string& u);
        void init();
        void parse(const string& s);
};

#endif	// __SIZE_H__

