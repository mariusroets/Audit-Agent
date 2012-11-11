
#include <set>
#include <list>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "sysprofileparser.h"
#include "commandparser.h"
#include "general.h"
#include "util.h"

SysProfileParser* SysProfileParser::mInstance = 0;

SysProfileParser* SysProfileParser::Instance()
{
    if (!mInstance) {
        mInstance = new SysProfileParser();
        mInstance->init();
    }
    return mInstance;
}

SysProfileParser::SysProfileParser()
{
    atexit(&cleanUp);
}

SysProfileParser::~SysProfileParser()
{
}

void SysProfileParser::init()
{
    CommandParser *cmd = CommandParser::Instance();
    cmd->parse("system_profiler", "> /tmp/audit-system-profile.txt");
    parse();
}
void SysProfileParser::cleanUp()
{
    if (mInstance)
        delete mInstance;
    mInstance = 0;
}

void SysProfileParser::parse()
{
    mNodes.clear();
    mIndentLevels.clear();
    mIndentLevels.push_back(0);

    string filename = "/tmp/audit-system-profile.txt";

    std::ifstream in(filename.c_str());
    if (!in) throw General::BadFile(filename);

    // Read file
    std::string line;
    while( getline(in, line) ) {
        // Skip empty lines
        if (line.empty()) continue;
        // First we get indentation level
        int pos = line.find_first_not_of(' ');
        // If there are no non-blank characters, skip the line
        if (pos < 0) continue;
        // Then we trim the string
        line = General::trim_string(line);
        // Tokenize the string
        tokenize(line);


        // Process fields
        int index = -1;

        if (fields.size() > 0) {
            // If the first element exist, it's the name, otherwise skip this line
            mNodes.push_back(Node());
            index = mNodes.size() - 1;
            mNodes[index].name = fields[0];
            mNodes[index].indentSize = pos;
            // The rest determines the indent level. It would have been easy if the creators
            // of system_profile used a constant indentation size, but they decided to randomize
            // it, so I have to keep a stack of indent sizes to undo indentation
            if (index == 0) {
                // This is the first element
                mNodes[index].indentLevel = 0;
            } else {
                if (mNodes[index-1].indentSize == mNodes[index].indentSize) {
                    // Since the indent size is the same as the previous node,
                    // the indent level must be the same
                    mNodes[index].indentLevel = mNodes[index-1].indentLevel;
                    mNodes[index].parent = mNodes[index-1].parent;
                } else if (mNodes[index-1].indentSize < mNodes[index].indentSize) {
                    // Since the indent size is higher than the previous node,
                    // the indent level must be increased by one
                    mNodes[index].indentLevel = mNodes[index-1].indentLevel + 1;
                    mIndentLevels.push_back(mNodes[index].indentSize);
                    mNodes[index].parent = index-1;
                } else if (mNodes[index-1].indentSize > mNodes[index].indentSize) {
                    // Indent level must decrease, but we don't know by how much, so
                    // retrace the stack created (mIndentLevels)
                    // Determine how many idents back
                    for (int j = 0; j < (int)mIndentLevels.size(); j++) {
                        if (mIndentLevels[j] == mNodes[index].indentSize) {
                            mNodes[index].indentLevel = j;
                            // Remove from indent stack
                            for (int k = j; k < (int)mIndentLevels.size(); k++) {
                                mIndentLevels.pop_back();
                            }
                            break;
                        }
                    }
                    mNodes[index].parent = tracebackParent(index-1, mNodes[index].indentLevel - 1);
                }
            }

        } else
            // If the first element exist, it's the name, otherwise skip this line
            continue;
        if (fields.size() == 2)
            // If there are 2 fields, it's a name/value pair
            mNodes[index].value = fields[1];
        else if (fields.size() > 2) {
            // Else there is a value that contains ":". Join them back together
            vector<string> val;
            val.resize(fields.size()-1); // Remove name
            // Join value that was split on ":"
            vector<string>::iterator it = fields.begin(); 
            copy(it+1,fields.end(), val.begin());
            mNodes[index].value = boost::algorithm::join(val,":");
        }
    }

}

int SysProfileParser::tracebackParent(int start, int targetLevel)
{
    int index = start;
    if (targetLevel < 0)
        return -1;
    do {
        index = mNodes[index].parent;
        int indentLevel = mNodes[index].indentLevel;
        if (indentLevel == targetLevel) {
            return index;
        }
    } while (index != -1);
    return -1;

}

void SysProfileParser::tokenize(const std::string& line)
{
    fields.clear();
    std::set<char> delimiters;
    delimiters.insert(':');

    std::string::const_iterator it;
    bool in_token = false;
    std::string field;
    for (it = line.begin(); it != line.end(); it++) {
        char c = (*it);
        if (delimiters.find(c) != delimiters.end()) {
        // If char is a delimiter
            if (in_token) {
                // Add the field to the list, clear the field variable
                fields.push_back(field);
                field = "";
                in_token = false;
            }
        } else {
        // If char is not a delimiter
            field += c;
            in_token = true;
        }
    }
    if (!field.empty()) fields.push_back(field);
    if (fields.size() >= 1)
        boost::trim(fields[0]);
    if (fields.size() >= 2)
        boost::trim(fields[1]);
}
bool SysProfileParser::isValueNode(Node n)
{
    return !n.value.empty();
}

string SysProfileParser::fullName(int start)
{

    int index = start;
    list<string> l;

    do {
        l.push_front(mNodes[index].name);
        index = mNodes[index].parent;
    } while (index != -1);

    return boost::algorithm::join(l,":");
}

string SysProfileParser::value(const vector<string>& key_list)
{
    int find_target = key_list.size()-1;
    for (int i = 0; i < (int)mNodes.size(); i++) {
        if (mNodes[i].name == key_list[find_target]) {
            int parent = i;
            bool found = true;
            for (int j = find_target-1; j >= 0; j--) {
                parent = mNodes[parent].parent;
                if (mNodes[parent].name != key_list[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return mNodes[i].value;
            }
        }
    }
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
vector<string> SysProfileParser::children(string parent)
{
    vector<string> list;
    for (int i = 0; i < (int)mNodes.size(); i++) {
        if (mNodes[i].parent == -1) continue;
        if (fullName(mNodes[i].parent) == parent) {
            list.push_back(mNodes[i].name);
        }
    }
    return list;

}
void SysProfileParser::showNodes()
{
    for (int i = 0; i < (int)mNodes.size(); i++) {
        cout << mNodes[i].name << "(" << mNodes[i].indentLevel << "," << mNodes[i].indentSize << ")" << endl;
        cout << "  * Full name : " << fullName(i) << endl;
        cout << "  * Value : " << mNodes[i].value << endl;
        cout << "  * Parent Address: " << mNodes[i].parent << endl;
        if (mNodes[i].parent != -1) {
            cout << "  * Parent : " << mNodes[mNodes[i].parent].name << endl;
            cout << "  * Parent Full name : " << fullName(mNodes[i].parent) << endl;
        }
    }

}
