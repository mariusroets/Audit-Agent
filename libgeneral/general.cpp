
#include <iostream>
#include "general.h"


std::string General::trim_string(const std::string& in)
{
    std::string str;

    // Trim Both leading and trailing white space
    size_t startpos = in.find_first_not_of(" \t\n\r"); // Find the first character position after excluding leading blank spaces
    size_t endpos = in.find_last_not_of(" \t\n\r"); // Find the first character position from reverse af

    // if all spaces or empty return an empty string
    if(( std::string::npos == startpos ) || ( std::string::npos == endpos)) {
        str = "";
    } else
        str = in.substr( startpos, endpos-startpos+1 );

    return str;
}
