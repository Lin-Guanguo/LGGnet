#ifndef LGGNET_TOOL_THREAD
#define LGGNET_TOOL_THREAD

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
 
#endif