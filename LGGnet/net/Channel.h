#ifndef LGGNET_TOOL_CHANNEL
#define LGGNET_TOOL_CHANNEL

#include "../tool/Noncopyable.h"

namespace LGG
{
class EventLoop;
    
class Channel : Noncopyable {
    const int fd_;
    EventLoop& loop_;
  public:
    static Channel& newChannel(EventLoop& loop, int fd);

    virtual void readCallBack() {};
    virtual void writeCallBack() {};
    virtual void errorCallBack() {};

  private:
    Channel(EventLoop& loop, int fd) : loop_(loop), fd_(fd) {};
    
};

} // namespace LGG

#endif