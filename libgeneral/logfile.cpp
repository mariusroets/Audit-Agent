/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#include <iostream>
#include <fstream>
#include <ctime>
#include "logfile.h"

LogFile::LogFile()
{
   mFormat = Plain; 
   mDebug = false;
   mFilepath = "";
   mPrefix.clear();
   mCustomFilename = false;
   createFilename();
   
}
void LogFile::writeDebug(const std::string& line, const std::string& tempPrefix)
{
   if (!mDebug)
      return;

   std::string debugPrefix;
   if (!tempPrefix.empty()) {
      debugPrefix = tempPrefix + ": DEBUG";
   } else {
      if (mPrefix.empty()) 
         debugPrefix = "DEBUG";
      else 
         debugPrefix = mPrefix + ": DEBUG";
   }
   writeLine(line, debugPrefix);
}
void LogFile::writeLine(const std::string& line, const std::string& tempPrefix)
{
   std::string lineToWrite;
   std::string padding;
   // if not custom filename, recreate the filename, because
   // date might have changed
   if (!mCustomFilename) {
      createFilename();
   }
   // Construct the full file path
   std::string filename;
   if (mFilepath.empty()) 
      filename = mFilename;
   else
      filename = mFilepath + "/" + mFilename;

   // Open the file
   std::ofstream log;
   log.open(filename.c_str(), std::ios_base::app);

   // Write time if required
   struct tm * date;
   time_t t;
   time(&t);
   date = localtime(&t);
   char dateString[20];
   switch (mFormat) {
       case Plain:
           break;
       case DateTimeStamped:
           sprintf(dateString, "%04d-%02d-%02d %02d:%02d:%02d", 
                   date->tm_year+1900, date->tm_mon+1, date->tm_mday,
                   date->tm_hour, date->tm_min, date->tm_sec);
           lineToWrite += std::string(dateString) + ": ";
           break;
       case TimeStamped:
           sprintf(dateString, "%02d:%02d:%02d", date->tm_hour, date->tm_min, date->tm_sec);
           lineToWrite += std::string(dateString) + ": ";
           break;
   }
   // Write prefix if required
   if (!tempPrefix.empty()) {
      lineToWrite += tempPrefix + ": ";
   } else if (!mPrefix.empty()) {
      lineToWrite += mPrefix + ": ";
   }

   // If there are multiple lines, add some padding to lines 2 onwards to line up.
   if (line.find("\n") != std::string::npos) {
      for (unsigned int i = 0; i < lineToWrite.size() ; ++i) {
         padding.append(" ");
      }
   }
   lineToWrite += line;
   size_t pos = lineToWrite.find('\n');
   while (pos != std::string::npos) {
       lineToWrite.replace(pos, 1, "\n"+padding);
       pos = lineToWrite.find('\n');
   }

   log << lineToWrite << std::endl;
   log.flush();
   log.close();
}
void LogFile::setFormat (Format format)
{
   mFormat = format;
}
void LogFile::createFilename()
{
    struct tm * date;
    time_t t;
    time(&t);
    date = localtime(&t);
    char dateString[9];
    sprintf(dateString, "%d%02d%02d", date->tm_year+1900, date->tm_mon+1, date->tm_mday);

    mFilename = std::string(dateString) + ".log";

}
void LogFile::setPath(const std::string& path)
{
   mFilepath = path;
}
void LogFile::setDebug(bool debug)
{
   mDebug = debug;
}
bool LogFile::debug()
{
   return mDebug;
}
void LogFile::setPrefix(const std::string& prefix)
{
   mPrefix = prefix;
}
std::string LogFile::prefix()
{
   return mPrefix;
}
void LogFile::setFilename(const std::string& filename)
{
   mFilename = filename;
   mCustomFilename = true;
}
void LogFile::removePrefix()
{
    mPrefix = "";
}
