#pragma once

#include "StaticClass.h"
#include "Log.h"
#include <functional>
#include <error.h>
#include <sys/wait.h>
#include <unistd.h>

namespace LGG
{

class Process{
    static void sigchldHandler(int sig){
        auto savedErrno = errno;
        pid_t childPid;
        while((childPid = ::waitpid(-1, NULL, WNOHANG)) > 0) {
            LOG_INFO("sigchldHandler reaped child ", childPid);
        }
        if(childPid == -1 && errno != ECHILD){
            LOG_ERROR("waitpid error");
        }
        errno = savedErrno;
    }

public:
    using ForkTask = std::function<void(void)>;

    static void iniSigchldHandler() {
        struct sigaction sa;
        sa.sa_handler = Process::sigchldHandler;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        if(sigaction(SIGCHLD, &sa, NULL) == -1){
            LOG_FATAL("sigaction error")
        }
    }
    
    //return subprocess's pid
    static pid_t ForkAndRun(const ForkTask& task) {
        pid_t pid = ::fork();
        switch(pid){
        case 0:
            task();
            exit(0);
            break;
        case -1:
            LOG_ERROR("fork error, return pid = ", pid, " main pid = ", ::getpid());
            break;
        default:
            LOG_TRACE("fork succeed, subprocess pid = ", pid, " main pid = ", ::getpid());
        }
        return pid; //父进程获得子进程id，子进程获得0
    }

    //return subprocess's pid
    static pid_t ForkAndExecve(const char* pathname, char* const argv[], char* const envp[]) {
        return ForkAndRun([pathname, argv, envp](){
            ::execve(pathname, argv, envp);
        });
    }

};

} // namespace LGG
