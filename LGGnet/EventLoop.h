#ifndef LGGNET_EVENTLOOP
#define LGGNET_EVENTLOOP

#include "Noncopyable.h"
#include "Thread.h"
#include <pthread.h>
#include <cassert>

namespace LGG
{

class EventLoop : Noncopyable {
    const pid_t threadId_;
  public:
    EventLoop();

    ~EventLoop();

    void loop();

    void assertInLoopThread() const { assert( isInLoopThread() ); }

    bool isInLoopThread() const { return threadId_ == CurrentThread::id(); } 

  private:
    
};

} // namespace LGG

#endif
