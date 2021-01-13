#pragma once

#include "StaticClass.h"
#include <pthread.h>

namespace LGG
{

class CurrentThread : StaticClass {
public:
    static pthread_t threadId() {
        return ::pthread_self();
    }
    
};
    
} // namespace LGG
