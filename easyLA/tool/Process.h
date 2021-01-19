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
    static void sigchldHandler(int sig);

public:
    using ForkTask = std::function<void(void)>;

    static void iniSigchldHandler();
    
    //return subprocess's pid
    static pid_t ForkAndRun(const ForkTask& task);

    //return subprocess's pid
    static pid_t ForkAndExecve(const char* pathname, char* const argv[], char* const envp[]);

};

} // namespace LGG
