#ifndef LGGNET_TOOL_CHANNEL
#define LGGNET_TOOL_CHANNEL

#include "../tool/Noncopyable.h"

namespace LGG
{
class EventLoop;
    
class Channel : Noncopyable {
    const int fd_;
    bool registered_ = false;
  public:
    static Channel& newChannelAndRegister(EventLoop& loop, int fd);
    static Channel* newChannel(int fd) { return new Channel(fd); }

    void registerInLoop(EventLoop& loop);

    virtual void readCallBack() {};
    virtual void writeCallBack() {};
    virtual void errorCallBack() {};

  private:
    Channel(int fd) : fd_(fd) {};
    
};

} // namespace LGG

#endif