
#include <ctime>
#include <fstream>
#include <iomanip>
#include "outputfile.h"
#include "infominer.h"


OutputFile::OutputFile(std::string filename) : mFilename(filename)
{
    mLineEnding = "\n";
}
void OutputFile::write()
{
    InfoMiner im;
    std::ofstream of(mFilename.c_str());
    // Write Header
    of << "[DATA]" << mLineEnding << mLineEnding;

    // Write the time
    struct tm * timeinfo;
    time_t rawtime;
    time ( &rawtime );
    timeinfo = localtime(&rawtime);
    of << std::setfill('0') << std::setw(2) << timeinfo->tm_mon+1 << "-";
    of << std::setfill('0') << std::setw(2) << timeinfo->tm_mday << "-";
    of << std::setfill('0') << std::setw(4) << timeinfo->tm_year+1900 << " ";
    of << std::setfill('0') << std::setw(2) << timeinfo->tm_hour << ":";
    of << std::setfill('0') << std::setw(2) << timeinfo->tm_min << ":";
    of << std::setfill('0') << std::setw(2) << timeinfo->tm_sec;
    of << mLineEnding << mLineEnding;


    of << im;
    of << "EOF=Yes";

    of.close();
}
void OutputFile::setLineEnding(const std::string& le)
{
    mLineEnding = le;
}
