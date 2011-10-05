/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __SYSPROFILEPARSER_H__
#define __SYSPROFILEPARSER_H__

#include <string>
#include <vector>
#include <map>
#include "tinyxml.h"

using namespace std;

class DictItem {
    public:
        enum DictItemType { String, Dict };
        DictItem();

        string name;
        DictItemType type;
        string value;
};
typedef map<string, DictItem> Dictionary;
class ArrayItem {
    public:
        enum ArrayItemType { String, Dict };
        ArrayItem();

        string item;
        Dictionary dict;
};
typedef vector<ArrayItem> Array;


class SysProfileParser
{
    public:
        enum PredefinedValue { IpAddress, MacAddress };
        SysProfileParser();
        ~SysProfileParser();
        void parse();
        string value(const vector<string>& key_list);
        string value(const string& key_list);
        string value(PredefinedValue pre);
        void traverse(TiXmlNode* node);
        string stackList();

    private:
        void setCurrentDataType(TiXmlNode* node);

        Array data;
        string current_element;
        string current_data_type;
        vector<string> element_stack;
};

#endif	// __SYSPROFILEPARSER_H__

