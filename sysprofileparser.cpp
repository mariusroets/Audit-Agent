
#include <iostream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
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
    mNodes.clear();
    CommandParser cmd;
    vector<string> lines = cmd.parse("cat /data/Dropbox/sys-profile-mac.txt");
    vector<vector<string> > fields = cmd.split(":");
    for (int i = 0; i < (int)fields.size(); ++i) {
        if (fields[i].size() > 0) {
            mNodes.push_back(Node());
            mNodes[i].name = fields[i][0];
        } else
            continue;
        if (fields[i].size() == 2)
            mNodes[i].value = fields[i][1];
        else if (fields[i].size() > 2) {
            vector<string> val;
            val.resize(fields[i].size()-1);
            vector<string>::iterator it = fields[i].begin();
            copy(it+1,fields[i].end(), val.begin());
            mNodes[i].value = boost::algorithm::join(val,":");
        }
    }
}

bool SysProfileParser::isValueNode(Node n)
{
    return !n.value.empty();
}

string SysProfileParser::value(const vector<string>& key_list)
{
    int find_counter = 0;
    int find_target = key_list.size()-1;
    for (int i = 0; i < (int)mNodes.size(); i++) {
        if ((find_counter == find_target) && (mNodes[i].name == key_list[find_counter]))
            return mNodes[i].value;
        if (mNodes[i].name == key_list[find_counter]) {
            find_counter++;
            if (find_counter > find_target)
                break;
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
