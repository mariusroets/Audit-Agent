/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __GENERAL_H__
#define __GENERAL_H__

#include <sstream>

using namespace std;

namespace General {
    std::string trim_string(const std::string& in);

    // Exceptions
    // Error opening a file
    class Exception {
        std::string n;
    public:
        Exception(const std::string& nm) : n(nm) {};
        std::string name() { return n; };
    };
    class BadFile : public Exception {
    public:
        BadFile(const std::string& nm) : Exception(nm) {};
    };
    class BadTransform : public Exception {
    public:
        BadTransform(const std::string& nm) : Exception(nm) {};
    };
    class IndexOutOfRange : public Exception {
    public:
        IndexOutOfRange(const std::string& nm) : Exception(nm) {};
    };
    class BadConversion : public Exception {
    public:
        BadConversion(const std::string& nm) : Exception(nm) {};
    };

    // Templates
    template <class T>
        T from_string(const string& s, ios_base& (*f)(ios_base&))
    {
        int t;
        istringstream iss(s);
        bool ok = !(iss >> f >> t).fail();
        if (!ok)
            throw General::BadConversion("Invalid conversion : " + s);
        return t;
    }
};

#endif	// __GENERAL_H__
