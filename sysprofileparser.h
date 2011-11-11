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
        indentLevel = -1;
        indentSize = -1;
        parent = -1;
    }
    string name;
    string value;
    int parent;
    int indentLevel;
    int indentSize;
};
typedef std::vector<std::string> FieldList;

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
        vector<string> children(string parent);
        void showNodes();
        string fullName(int start);
        int tracebackParent(int start, int targetLevel);

    private:
        vector<Node> mNodes;

        bool isValueNode(Node n);
        void tokenize(const std::string& line);
        FieldList fields;
        std::vector<FieldList> lines;
        std::vector<int> mIndentLevels;
};

extern SysProfileParser *SYS;

#endif	// __SYSPROFILEPARSER_H__

