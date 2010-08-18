/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#include "logfile.h"

LogFile *LogFile::file = 0;

LogFile::LogFile()
{
   mDebug = false;
   mFilepath = "";
   mPrefix.clear();
   mCustomFilename = false;
   createFilename();
}
LogFile* LogFile::logFile()
{
   if (!file) {
      file = new LogFile();
   }
   return file;
}
void LogFile::writeDebug(const std::string& line, const std::string& tempPrefix)
{
   if (!mDebug)
      return;

   unsigned long threadId = (unsigned long)QThread::currentThreadId();

   std::string debugPrefix;
   if (!tempPrefix.isEmpty()) {
      debugPrefix = tempPrefix + ": DEBUG";
   } else {
      if (!mPrefix.contains(threadId)) 
         debugPrefix = "DEBUG";
      else 
         debugPrefix = mPrefix[threadId] + ": DEBUG";
   }
   writeLine(line, debugPrefix);
}
void LogFile::writeLine(const std::string& line, const std::string& tempPrefix)
{
   std::string lineToWrite;
   unsigned long threadId = (unsigned long)QThread::currentThreadId();
   std::string padding;
   // if not custom filename, recreate the filename, because
   // date might have changed
   if (!mCustomFilename) {
      createFilename();
   }
   // Construct the full file path
   std::string filename;
   if (mFilepath.isEmpty()) 
      filename = mFilename;
   else
      filename = mFilepath + "/" + mFilename;

   // Open the file
   QFile log(filename);
   if (!log.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
      return;

   QTextStream out(&log);
   // Write time if required
   switch (mFormat) {
      case Plain:
         break;
      case TimeStamped:
         QTime time;
         time = QTime::currentTime();
         //out << time.toString("HH:mm:ss") << ": ";
         lineToWrite += time.toString("HH:mm:ss") + ": ";
         break;
   }
   // Write prefix if required
   if (!tempPrefix.isEmpty()) {
      lineToWrite += tempPrefix + ": ";
   } else if (mPrefix.contains(threadId)) {
      lineToWrite += mPrefix[threadId] + ": ";
   }

   // If there are multiple lines, add some padding to lines 2 onwards to line up.
   if (line.contains("\n")) {
      for (int i = 0; i < lineToWrite.size() ; ++i) {
         padding.append(" ");
      }
   }
   lineToWrite += line;
   lineToWrite = lineToWrite.replace('\n', "\n"+padding);

   out << lineToWrite << endl;
   log.flush();
   log.close();
}
void LogFile::setFormat (Format format)
{
   mFormat = format;
}
void LogFile::createFilename()
{
   QDate date;
   date = QDate::currentDate();

   mFilename = date.toString("yyyyMMdd") + ".log";

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
   unsigned long threadId = (unsigned long)QThread::currentThreadId();
   if (!mPrefix.contains(threadId)) {
       mPrefix.insert(threadId, prefix);
   } else {
       mPrefix[threadId] = prefix;
   }
}
std::string LogFile::prefix()
{
   unsigned long threadId = (unsigned long)QThread::currentThreadId();
   if (mPrefix.contains(threadId)) {
       return mPrefix[threadId];
   } 
   return "";
}
void LogFile::setFilename(const std::string& filename)
{
   mFilename = filename;
   mCustomFilename = true;
}
void LogFile::removePrefix()
{
   unsigned long threadId = (unsigned long)QThread::currentThreadId();
   mPrefix.remove(threadId);
}
