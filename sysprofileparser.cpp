
#include <iostream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "sysprofileparser.h"
#include "commandparser.h"

SysProfileParser::SysProfileParser()
{
    current_element = "";
    current_data_type = "";
    element_stack.clear();
    //data.clear();
}

SysProfileParser::~SysProfileParser()
{
}

void SysProfileParser::parse()
{
    string pFilename = "sys-profile-mac.xml";
    TiXmlDocument doc("sys-profile-mac.xml");
    doc.LoadFile();
    traverse(&doc);
}
void SysProfileParser::traverse(TiXmlNode* node)
{
    if ( !node ) return;

    TiXmlNode* child;
    int t = node->Type();
    string value;

    switch ( t ) {
        case TiXmlNode::TINYXML_ELEMENT:
            current_element = node->ValueStr();
            element_stack.push_back(current_element);
            cout << "pushing Element: [" << current_element << "]" << endl;
            break;

        case TiXmlNode::TINYXML_TEXT:
            value = node->ToText()->ValueStr();
            //cout << "Element Stack: " << stackList() << endl;
            //cout << "Element: [" << current_element << "]" << endl;
            //cout << "Text: [" << value << "]" << endl;
            if (value == "_dataType") {
                setCurrentDataType(node->Parent());
                cout << "Data Type : " << value << "," << current_data_type << endl;
            }
            break;

        default:
            break;
    }
    if (current_data_type == "SPSerialATADataType") {
        // Serial ATA, store as hard drive information
        cout << "Element Stack: " << stackList() << endl;
        //cout << "Element: [" << current_element << "]" << endl;
    }
    for ( child = node->FirstChild(); child != 0; child = child->NextSibling()) {
        traverse(child);
    }
    if (t == TiXmlNode::TINYXML_ELEMENT) {
        element_stack.pop_back();
    }
}
void SysProfileParser::setCurrentDataType(TiXmlNode* node)
{
    TiXmlNode* sibling = node->NextSibling();
    TiXmlText* text = sibling->FirstChild()->ToText();
    current_data_type = text->ValueStr();

}
string SysProfileParser::stackList()
{
    string s = element_stack[0];
    for (int i = 1; i < (int)element_stack.size(); i++) {
        s += ";" + element_stack[i];
    }
    return s;
}


string SysProfileParser::value(const vector<string>& key_list)
{
    // Nothing found
    return "";
}
string SysProfileParser::value(const string& key_list)
{
    string splitString = ":";
    vector<string> list;
    boost::split(list, key_list, boost::is_any_of(splitString), boost::token_compress_on);
    return value(list);
}
string SysProfileParser::value(PredefinedValue pre)
{
    switch (pre) {
        case IpAddress:
            return value("Network:Ethernet:IPv4:Addresses");
        case MacAddress:
            return value("Network:Ethernet:Ethernet:MAC Address");
        default :
            return "";
    }
}
