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

using namespace std;

struct Node {
    Node() {
        name = "";
        value = "";
    }
    string name;
    string value;
};

class SysProfileParser
{
    public:
        SysProfileParser();
        ~SysProfileParser();
        void parse();
        string value(const vector<string>& key_list);

    private:
        vector<Node> mNodes;

        bool isValueNode(Node n);
};

#endif	// __SYSPROFILEPARSER_H__

