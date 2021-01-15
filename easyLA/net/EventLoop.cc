#include "EventLoop.h"
#include "Channel.h"
#include "../tool/Thread.h"
#include "../tool/Log.h"
#include <poll.h>

using namespace LGG;
using namespace std;

__thread EventLoop* loopInThisThread_t = nullptr;

EventLoop::EventLoop() 
  : threadId_(Thread::currentThreadId())
{
    LOG_TRACE("EventLoop creart ", this, " in thread ", threadId_)
	if(loopInThisThread_t == nullptr){
		loopInThisThread_t = this;
	}else{
		LOG_FATAL("Another EventLoop ", loopInThisThread_t, " exists in this this thread ", threadId_ );
	}
}

EventLoop::~EventLoop() {
	loopInThisThread_t = nullptr;
}

void EventLoop::loop() {
	assertInLoopThread();

	::poll(NULL, 0, 5000);

	LOG_TRACE("EventLoop ", this, " loop start")
}

void EventLoop::assertInLoopThread() {
	if(!isInLoopThread()){
		LOG_FATAL("assertInLoopThread == false thread ", threadId_, "!=" , Thread::currentThreadId());
		assert(isInLoopThread());
	}
}

bool EventLoop::isInLoopThread() const { 
    return threadId_ == Thread::currentThreadId(); 
} 

void EventLoop::addChannel(ChannelPtr channelptr) { 
    LOG_TRACE("channel ",channelptr.get(), " register in loop ", this); 
    channelList_.push_back(std::move(channelptr));
}