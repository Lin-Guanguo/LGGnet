#ifndef LGGNET_EVENTLOOP
#define LGGNET_EVENTLOOP

#include "Noncopyable.h"
#include <pthread.h>

namespace LGG
{

class EventLoop : Noncopyable {
    const pid_t threadId_;
  public:
    EventLoop();

    ~EventLoop();

    void loop();

    bool isInLoopThread() const { return threadId_ == 0; } //

  private:
    
};

}//end LGG

#endif
