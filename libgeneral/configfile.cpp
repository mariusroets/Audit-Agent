
#include <set>
#include "configfile.h"

ConfigFile::ConfigFile(const std::string& f) : DelimitedFile(f)
{
    // Set of delimiters
    std::set<char> delimiters;
    delimiters.insert('=');
    //delimiters.insert(' ');
    setDelimiters(delimiters);
    // Set of comment characters
    std::set<char> c;
    c.insert('#');
    setCommentChars(c);
    read();

}

std::string ConfigFile::getValueAsString(const std::string name)
{
    first();
    do {
        if ((*this)[0] == name) {
            return (*this)[1];
        }
    } while (next());
    return "";

}
int ConfigFile::getValueAsInt(const std::string name)
{
    first();
    do {
        if ((*this)[0] == name) {
            return asInt(1);
        }
    } while (next());
    // TODO: This should throw an error, otherwise there is no way to tell 
    // when we did not find the int
    return 0;
}
bool ConfigFile::getValueAsBool(const std::string name)
{
    first();
    do {
        if ((*this)[0] == name) {
            return asBool(1);
        }
    } while (next());
    // TODO: This should throw an error, otherwise there is no way to tell 
    // when we did not find the bool
    return false;
}
