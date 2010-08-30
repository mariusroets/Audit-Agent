
#include <boost/algorithm/string.hpp>
#include "util.h"
#include "commandparser.h"

CommandParser::CommandParser()
{
}

CommandParser::~CommandParser()
{
}

std::vector<std::string> CommandParser::parse(std::string cmd)
{
    std::string s = Util::exec( cmd );
    mLines.clear();
    // Split output in vector of lines
    boost::split(mLines, s, boost::is_any_of("\n\r"), boost::token_compress_on);
    for (unsigned int i = 0; i < mLines.size() ; ++i) {
        boost::trim(mLines[i]);
        // Skip empty lines
        if (mLines[i].empty())
            continue;
    }
    // remove empty lines
    std::remove(mLines.begin(), mLines.end(), "");

    return mLines;
}
std::vector<std::vector<std::string> > CommandParser::split(std::string splitString)
{
    mFields.clear();
    for (unsigned int i = 0; i < mLines.size() ; ++i) {
        std::vector<std::string> fields;
        boost::split(fields, mLines[i], boost::is_any_of(splitString), boost::token_compress_on);
        for (int j = 0; j < (int)fields.size(); ++j) {
            boost::trim(fields[j]);
        }
        mFields.push_back(fields);
    }
    return mFields;

}
void CommandParser::printLines()
{
    for (unsigned int i = 0; i < mLines.size() ; ++i) {
        std::cout << mLines[i] << std::endl;
    }
}
void CommandParser::printFields()
{
    for (unsigned int i = 0; i < mFields.size() ; ++i) {
        for (unsigned int j = 0; j < mFields[i].size() ; ++j) {
            std::cout << mFields[i][j] << ":";
        }
            std::cout << std::endl;
    }
}
