
#include <boost/algorithm/string.hpp>
#include "util.h"
#include "commandparser.h"

CommandParser* CommandParser::mInstance = 0;

CommandParser* CommandParser::Instance()
{
    if (!mInstance) {
        mInstance = new CommandParser();
        mInstance->init();
    }
    return mInstance;
}
CommandParser::CommandParser()
{
    // "which" is used to determine the paths of other commands. It is the
    // only command which is assumed to be in the path
    mCmds["which"] = "which";
    mCmds["hostname"] = "";
    mCmds["fdisk"] = "";
    mCmds["df"] = "";
    mCmds["ifconfig"] = "";
    mCmds["lsb_release"] = "";
    mCmds["cat"] = "";
    mCmds["pkgutil"] = "";
    mCmds["rpm"] = "";
    mCmds["uname"] = "";
    atexit(&cleanUp);
}

CommandParser::~CommandParser()
{
}
void CommandParser::cleanUp()
{
    if (mInstance)
        delete mInstance;
    mInstance = 0;
}
void CommandParser::init()
{
    std::map<std::string,std::string>::iterator it;
    for (it = mCmds.begin();it != mCmds.end(); it++) {
        mInstance->parse("which", (*it).first, true);
        std::vector<std::string> lines = mInstance->lines();
        if (lines[0].find(":") == std::string::npos) {
            (*it).second = lines[0];
        }
    }
    //for (it = mCmds.begin();it != mCmds.end(); it++) {
    //    std::cout << (*it).first << " - " << (*it).second << std::endl;
    //}
}

void CommandParser::parse(std::string cmd, std::string params, bool su)
{
    std::string c = mCmds[cmd];
    if (c.empty()) {
        return;
    }
    if (su) {
        c = "sudo " + c;
    }
    if (!params.empty()) {
        c = c + " " + params;
    }
    std::string s = Util::exec( c );
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

}
void CommandParser::split(std::string splitString)
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
}
std::vector<std::string> CommandParser::lines()
{
    return mLines;
}
std::vector<std::vector<std::string> > CommandParser::fields()
{
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
