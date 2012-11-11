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
        static SysProfileParser* Instance();
        static void cleanUp();

        enum PredefinedValue { IpAddress, MacAddress };
        void parse();
        string value(const vector<string>& key_list);
        string value(const string& key_list);
        string value(PredefinedValue pre);
        vector<string> children(string parent);
        void showNodes();
        string fullName(int start);
        int tracebackParent(int start, int targetLevel);

    private:
        SysProfileParser();
        ~SysProfileParser();
        static SysProfileParser* mInstance;
        // Not copyable
        SysProfileParser(SysProfileParser const&);
        SysProfileParser operator=(SysProfileParser const&);

        vector<Node> mNodes;

        void init();
        bool isValueNode(Node n);
        void tokenize(const std::string& line);
        FieldList fields;
        std::vector<FieldList> lines;
        std::vector<int> mIndentLevels;
};

#endif	// __SYSPROFILEPARSER_H__

