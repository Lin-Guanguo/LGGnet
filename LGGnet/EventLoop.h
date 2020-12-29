#ifndef LGGNET_EVENTLOOP
#define LGGNET_EVENTLOOP

#include "Noncopyable.h"
#include "Thread.h"
#include <cassert>

namespace LGG
{

class EventLoop : Noncopyable {
    const pthread_t threadId_;
    bool looping_;
  public:
    EventLoop();

    ~EventLoop();

    void loop();

    void assertInLoopThread();

    bool isInLoopThread() const { return threadId_ == CurrentThread::threadId(); } 

  private:
    
};

} // namespace LGG

#endif
