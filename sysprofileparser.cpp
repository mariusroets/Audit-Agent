
#include <iostream>
#include "sysprofileparser.h"
#include "commandparser.h"

SysProfileParser::SysProfileParser()
{
}

SysProfileParser::~SysProfileParser()
{
}

void SysProfileParser::parse()
{
    CommandParser cmd;
    vector<string> lines = cmd.parse("cat /data/Dropbox/sys-profile-mac.txt");
    vector<vector<string> > fields = cmd.split(":");
    Node *p = 0;
    for (int i = 0; i < (int)fields.size(); ++i) {
        Node *n = new Node();
        n->name = fields[i][0];
        n->value = fields[i][1];
        if (!p) {
            // There exists no previous nodes, this is the first root node
            mRoot = n;
            p = n;
            continue;
        }
        if (isValueNode(p)) {
            // Previous node is a value
            if (isValueNode(n)) {
                p->next_sibling = n;
                n->parent = p->parent;
            } else {

            }

        } else {
            // Previous node is a node
            n->parent = p;
            p->first_child = n;
        }


        cout << fields[i][0] << ":" << fields[i][1] << endl;
        p = n;
    }
}

bool SysProfileParser::isRootNode(Node *n)
{
    return !n->parent;
}

bool SysProfileParser::isValueNode(Node *n)
{
    return !n->value.empty();
}
