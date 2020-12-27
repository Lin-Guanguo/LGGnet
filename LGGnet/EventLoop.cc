#include "EventLoop.h"

using namespace LGG;

EventLoop::EventLoop() 
  : threadId_(CurrentThread::id()) 
{

};

EventLoop::~EventLoop() {

}

void EventLoop::loop() {

}