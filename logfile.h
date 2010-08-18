/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/


#ifndef __LOGFILE_H__
#define __LOGFILE_H__

#include <string>
#include <map>

class LogFile
{
   public:
      enum Format {
         Plain, /**< The output is written to file as is */
         TimeStamped /**< Timestamp is prepended to output */
      };
      /** Writes the line "line" to the logfile, followed by a line break */
      void writeLine(const std::string& line, const std::string& tempPrefix="");
      /** Writes the line "line" to the logfile, followed by a line break 
       * Only written if mDebug is true */
      void writeDebug(const std::string& line, const std::string& tempPrefix="");
      /** Sets the for to one of the formats specified by "Format" */
      void setFormat (Format format);
      /** Sets the path where the log file will be written to */
      void setPath(const std::string& path);
      /** Sets the logfile into debug mode. */
      void setDebug(bool debug);
      /** Returns the debug status of the logfile */
      bool debug();
      /** Sets a string to be prefixed to every line output */
      void setPrefix(const std::string& prefix);
      /** Remove the prefix */
      void removePrefix();
      /** Returns the current prefix string */
      std::string prefix();
      void setFilename(const std::string& filename);

      static LogFile* logFile();
   private:
      /** Constructor. A filename of the form yyyyMMdd.log is created */
      LogFile();
      void createFilename();

      std::string mFilename;
      std::string mFilepath;
      Format mFormat;
      bool mDebug;
      map <unsigned long, std::string> mPrefix;
      bool mCustomFilename;

      static LogFile *file;

};

#endif	// __LOGFILE_H__

