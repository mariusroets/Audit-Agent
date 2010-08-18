

#include "daemon.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdexcept>
#include <sstream>

Daemon *Daemon::mDaemon = 0;

Daemon::Daemon(const std::string& key) : mKey(key)
{
   mStdInputFile = "/dev/null";
   mStdOutputFile = "/dev/null";
   mErrOutputFile = "/dev/null";
   mRunningDirectory = "/";
   mPid = 0;
   //qDebug() << "Daemon: Contructing Daemon object";
   mStatus = lock();
   switch (mStatus) {
       case Daemon::New:
           break;
       case Daemon::Error:
           throw std::runtime_error("Could not create a lock file");
           break;
       case Daemon::Running:
           mPid = getPid();
           break;
   }
}
Daemon::~Daemon()
{
   //qDebug() << "Daemon: Destructor";
   //mSharedMem->detach();
   //delete mSharedMem;
}
Daemon* Daemon::daemon(const std::string& key)
{
   if (!mDaemon) {
      mDaemon = new Daemon(key);
   }
   return mDaemon;
}
Daemon::Status Daemon::status()
{
   return mStatus;
}
pid_t Daemon::getPid()
{
    return mPid;
}
void Daemon::start()
{
    if (mStatus != Daemon::New) {
        //qDebug() << "Daemon: The process is already running";
        return;
    }
    // Fork the daemon
    pid_t pid = fork();
    if (pid) 
        exit(0);
    pid = fork();
    if (pid) 
        exit(0);
    // Get the process id
    mPid = getpid();
    // Create a new process group
    setsid();
    // Set file creation permission
    umask(027);
    // Close all file descriptors
    for (int i = getdtablesize(); i >= 0; --i) 
        close(i);
    // Redirect standard I/O
    int fd0 = open(mStdInputFile.c_str(), O_RDONLY);
    int fd1 = open(mStdOutputFile.c_str(), O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    int fd2 = open(mErrOutputFile.c_str(), O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    if (fd0 != STDIN_FILENO || fd1 != STDOUT_FILENO || fd2 != STDERR_FILENO) {
        //Unexpected file descriptors
        throw std::runtime_error("new standard file descriptors were not opened as expected");
    }

    // Set the running directory
    if (!mRunningDirectory.empty() && chdir(mRunningDirectory.c_str()) < 0) {
        // Error
        throw std::runtime_error(strerror(errno));
    }

    // Set up signal handler
    signal(SIGHUP, Daemon::signalHandler); // hangup signal
    signal(SIGTERM, Daemon::signalHandler); // termination(kill) signal
    signal(SIGCHLD,SIG_IGN); // ignore child
    signal(SIGTSTP,SIG_IGN); // ignore tty signals
    signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);

    // Logging

    mStatus = Daemon::Running;

}
Daemon::Status Daemon::lock()
{
    int lfp = open("/tmp/exampled.lock", O_RDWR|O_CREAT,0640);
    if (lfp < 0) 
        return Daemon::Error; // can't open
    if (lockf(lfp,F_TLOCK, 0) < 0) 
        return Daemon::Running; // can't lock
    std::ostringstream o;
    o << mPid;
    std::string pid(o.str());
    write(lfp, pid.c_str(), pid.length()); // record pid to lockfile
    return Daemon::New;
}
void Daemon::stop()
{
    if (mStatus != Daemon::Running) {
        //qDebug() << "Daemon: The process is not running";
        return;
    }
    //qDebug() << "Daemon: Stopping daemon with PID : " << mPid;
    exit(0);
}
void Daemon::setFiles(const std::string& inputFile, const std::string& outputFile, const std::string& errorFile)
{
    mStdInputFile = inputFile;
    mStdOutputFile = outputFile;
    mErrOutputFile = errorFile;
}
pid_t Daemon::pid()
{
    return mPid;
}
void Daemon::signalHandler(int signal)
{
    switch (signal) {
        case SIGTERM:
            if (mDaemon) {
                //qDebug() << "Daemon: Deleting daemon singleton";
                delete mDaemon;
                exit(0);
            }
        case SIGHUP:
            break;
    }
}

