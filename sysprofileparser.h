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
#include "harddrive.h"

using namespace std;

/* class ArrayItem;
typedef vector<ArrayItem> Array;
class DictItem {
    public:
        enum DictItemType { String, Dict, Array, Integer };
        DictItem();

        DictItemType type;
        string str_val;
        int int_val;
        DictItem *dict_val;
        Array arr_val;
};
typedef map<string, DictItem> Dictionary;
class ArrayItem {
    public:
        enum ArrayItemType { String, Dict };
        ArrayItem();

        string item;
        Dictionary dict;
}; */


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
        // Disk drive information
        std::map<std::string, HardDrive::DiskDevice> mDevices;
        void setCurrentDataType(TiXmlNode* node);

        //Array data;
        string current_element;
        string current_data_type;
        vector<string> element_stack;
};

#endif	// __SYSPROFILEPARSER_H__

