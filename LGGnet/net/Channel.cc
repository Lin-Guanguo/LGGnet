#include "Channel.h"
#include "EventLoop.h"

using namespace std;
using namespace LGG;

Channel& Channel::newChannel(EventLoop& loop, int fd) {
    auto p = new Channel(loop, fd);
    loop.addChannel(unique_ptr<Channel>(p));
    return *p;
}