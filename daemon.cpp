

#include "daemon.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/file.h>
#include <string.h>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <fstream>
#include "util.h"

Daemon *Daemon::mDaemon = 0;

Daemon::Daemon(const std::string& key) : mKey(key)
{
    mStdInputFile = "/dev/null";
    mStdOutputFile = "/dev/null";
    mErrOutputFile = "/dev/null";
    mRunningDirectory = "/";
    mPid = 0;
    //qDebug() << "Daemon: Contructing Daemon object";
    mLockFile = std::string("/tmp/") + mKey + std::string(".lock");
    mStatus = lock();
    switch (mStatus) {
        case Daemon::New:
            break;
        case Daemon::Error:
            throw std::runtime_error("Could not create a lock file");
            break;
        case Daemon::Running:
            getPid();
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
void Daemon::setExecutable(const std::string& exe)
{
    mExecutable = exe;
}
Daemon::Status Daemon::status()
{
   return mStatus;
}
std::string Daemon::statusStr()
{
    switch (mStatus) {
        case Daemon::New:
            return "Daemon is starting up, or not running";
        case Daemon::Running:
            return "Daemon is running";
        case Daemon::Error:
            return "Daemon is in an Error state";
        default:
            return "Daemon is in unknown state";
    }
}
pid_t Daemon::getPid()
{
    std::ifstream f(mLockFile.c_str());
    f >> mPid;
    f.close();
    return mPid;
}
void Daemon::setPid(pid_t pid)
{
    std::ofstream f(mLockFile.c_str());
    f << mPid;
    f.close();
}
bool Daemon::start()
{
    if (mStatus != Daemon::New) {
        //qDebug() << "Daemon: The process is already running";
        return false;
    }
    // Fork the daemon
    pid_t pid = fork();
    if (pid) 
        exit(0);
    // Create a new process group
    setsid();
    // Set file creation permission
    umask(027);
    pid = fork();
    if (pid) 
        exit(0);
    // Get the process id
    mPid = getpid();
    setPid(mPid);
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
    return true;

}
Daemon::Status Daemon::lock()
{
    if (Util::fileExists(mLockFile)) {
        getPid();
        char procfile[200];
        sprintf(procfile, "/proc/%d/cmdline", mPid);
        std::ifstream f(procfile);
        std::string cmdline;
        getline(f, cmdline);
        f.close();
        size_t pos = cmdline.find_last_of("/");
        size_t end = mExecutable.size();
        if (cmdline.substr(pos+1,end) == mExecutable) {
            return Daemon::Running;
        } else {
            unlink(mLockFile.c_str());
            return Daemon::New;
        }

    } else {
        return Daemon::New;
    }
}
void Daemon::stop()
{
    if (mStatus != Daemon::Running) {
        std::cout << "Daemon: The process is not running\n";
        return;
    }
    std::cout << "Daemon: Stopping daemon with PID : " << mPid << std::endl;
    unlink(mLockFile.c_str());
    kill(mPid, SIGTERM);
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
void Daemon::signalHandler(int sig)
{
    switch (sig) {
        case SIGTERM:
            signal(SIGTERM, SIG_IGN); // Ignore
            if (mDaemon) {
                if (mDaemon->status() == Daemon::Running) {
                    mDaemon->stop();
                }
                //qDebug() << "Daemon: Deleting daemon singleton";
                delete mDaemon;
                exit(0);
            }
        case SIGHUP:
            //signal(SIGHUP, SIG_IGN); // hangup signal
            break;
    }
}

