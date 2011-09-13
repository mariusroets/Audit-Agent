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
        parent = 0;
        first_child = 0;
        next_sibling = 0;
        name = "";
        value = "";
    }
            
    Node *parent;
    Node *first_child;
    Node *next_sibling;
    string name;
    string value;
};

class SysProfileParser
{
    public:
        SysProfileParser();
        ~SysProfileParser();
        void parse();

    private:
        Node* mRoot;

        bool isRootNode(Node *n);
        bool isValueNode(Node *n);
};

#endif	// __SYSPROFILEPARSER_H__

