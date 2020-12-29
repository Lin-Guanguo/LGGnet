#include "EventLoop.h"
#include "Log.h"
#include <poll.h>

using namespace LGG;

__thread EventLoop* loopInThisThread_t = nullptr;

EventLoop::EventLoop() 
  : threadId_(CurrentThread::threadId())
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
		LOG_FATAL("assertInLoopThread == false thread ", threadId_, "!=" , CurrentThread::threadId());
		assert(isInLoopThread());
	}
}