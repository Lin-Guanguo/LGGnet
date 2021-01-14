#pragma once

#include "../tool/Noncopyable.h"
#include <cassert>
#include <vector>
#include <memory>


namespace LGG
{
class Channel;

class EventLoop : Noncopyable {
    using ChannelPtr = std::unique_ptr<Channel>;
    using ChannelList = std::vector<ChannelPtr>;

    const pthread_t threadId_;
    ChannelList channelList_;

  public:
    EventLoop();

    ~EventLoop();

    void loop();

    //EventLoop创建线程和启动线程必须一致
    void assertInLoopThread();

    bool isInLoopThread() const;

    void addChannel(ChannelPtr channelptr);

  private:
    
};

} // namespace LGG

