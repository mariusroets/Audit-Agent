
#include <boost/algorithm/string.hpp>
#include "util.h"
#include "commandparser.h"
#include "log.h"

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
    // Dmidecode is not installed but has a custom path
    std::string dmi_path = Util::SETTINGS->install_path + "/dmidecode/dmidecode";
    mCmds["dmidecode"] = dmi_path;
    mCmds["hostname"] = "";
    mCmds["fdisk"] = "";
    mCmds["df"] = "";
    mCmds["ifconfig"] = "";
    mCmds["lsb_release"] = "";
    mCmds["cat"] = "";
    mCmds["pkgutil"] = "";
    mCmds["rpm"] = "";
    mCmds["uname"] = "";
    mCmds["whoami"] = "";
    mCmds["hdparm"] = "";
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
        if (!(*it).second.empty()) {
            continue;
        }
        mInstance->parse("which", (*it).first, true);
        std::vector<std::string> lines = mInstance->lines();
        if (lines[0].find(":") == std::string::npos) {
            (*it).second = lines[0];
        }
    }
    LogFile *l = Log::Instance();
    for (it = mCmds.begin();it != mCmds.end(); it++) {
        l->writeDebug((*it).first + " - " + (*it).second);
    }
}

void CommandParser::parse(std::string cmd, std::string params, bool su)
{
    if (!mCmds.count(cmd)) {
        return;
    }
    std::string c = "\"" + mCmds[cmd] + "\"";

    if (su) {
        c = "sudo " + c;
    }
    if (!params.empty()) {
        c = c + " " + params;
    }
    LogFile *l = Log::Instance();
    l->writeDebug(c);
    std::string s = Util::exec( c );
    mLines.clear();
    std::vector<std::string>lines;
    // Split output in vector of lines
    boost::split(lines, s, boost::is_any_of("\n\r"), boost::token_compress_on);
    for (unsigned int i = 0; i < lines.size() ; ++i) {
        boost::trim(lines[i]);
        // Skip empty lines
        if (lines[i].empty())
            continue;
        mLines.push_back(lines[i]);
    }

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
