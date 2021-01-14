#pragma once

#include "StaticClass.h"
#include "Log.h"
#include <functional>
#include <unistd.h>

namespace LGG
{

class Process{
public:
    using ForkTask = std::function<void(void)>;
    
    static pid_t ForkAndRun(const ForkTask& task) {
        pid_t pid = ::fork();
        if( pid == 0 ){    //subprocess
            task();
            exit(0);
        }else if(pid < 0) {
            LOG_ERROR("fork error, return pid = ", pid);
        }else {
            LOG_TRACE("fork succeed, subprocess pid = ", pid);
        }
        return pid; //父进程获得子进程id，子进程获得0
    }

};

} // namespace LGG
