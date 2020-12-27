#ifndef LGGNET_THREAD
#define LGGNET_THREAD

#include <pthread.h>

namespace LGG
{

class Thread {

};

namespace CurrentThread {
    pthread_t id() { return pthread_self(); }
}
    
} // namespace LGG
 
#endif