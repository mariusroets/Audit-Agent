/***************************************************************************
                          filename - description
                             -------------------
    begin                : 
    copyright            : (C) yyyy [name] <[email]>
 ***************************************************************************/

#ifndef __DAEMON_H__
#define __DAEMON_H__

#include <string>
#define SHARED_MEM_SIZE 15

class Daemon
{
   public:
      enum Status { 
         New,
         Running,
         Error
      };
      ~Daemon();
      bool start();
      void setFiles(const std::string& inputFile,
                    const std::string& outputFile,
                    const std::string& errorFile);
      pid_t pid();
      void stop();
      Status status();
      std::string statusStr();
      static void signalHandler(int signal);
      static Daemon* daemon(const std::string& key);
    
   private:
      Daemon(const std::string& key);
      pid_t mPid;
      std::string mKey;
      std::string mStdOutputFile;
      std::string mStdInputFile;
      std::string mErrOutputFile;
      std::string mRunningDirectory;
      std::string mLockFile;
      Status mStatus;

      static Daemon *mDaemon;

      Status lock();
      pid_t getPid();
      void setPid(pid_t pid);



};

#endif	// __DAEMON_H__

