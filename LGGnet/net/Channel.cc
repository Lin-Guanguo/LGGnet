#include "Channel.h"
#include "EventLoop.h"

using namespace std;
using namespace LGG;

Channel& Channel::newChannelAndRegister(EventLoop& loop, int fd) {
    auto p = new Channel(fd);
    p->registerInLoop(loop);
    return *p;
}

void Channel::registerInLoop(EventLoop& loop) {
    assert(!registered_);
    loop.addChannel(unique_ptr<Channel>(this));
    registered_ = true;
}