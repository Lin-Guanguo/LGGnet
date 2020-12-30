#ifndef LGGNET_NET_EVENTLOOP
#define LGGNET_NET_EVENTLOOP

#include "../tool/Noncopyable.h"
#include "../tool/Thread.h"
#include <cassert>

namespace LGG
{

class EventLoop : Noncopyable {
    const pthread_t threadId_;
  public:
    EventLoop();

    ~EventLoop();

    void loop();

    //EventLoop创建线程和启动线程必须一致
    void assertInLoopThread();

    bool isInLoopThread() const { return threadId_ == CurrentThread::threadId(); } 

  private:
    
};

} // namespace LGG

#endif
