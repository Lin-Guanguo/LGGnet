#pragma once

#include "StaticClass.h"
#include "Noncopyable.h"
#include "Log.h"
#include <pthread.h>
#include <memory>
#include <cassert>

namespace LGG
{

class ThreadAPI : StaticClass {
private:
    template<typename Runable>
    class Thread : Noncopyable, public std::enable_shared_from_this<Thread<Runable>> {  
        //document: (ie. public inheritance is mandatory) (since C++17)
    private:
        pthread_t id_;
        Runable task_;
        volatile bool detach_ = false;
        volatile bool started_ = false;
    public:
        Thread(const Runable& task) : task_(task) {
            LOG_TRACE("A Thread obj Constructor ", this);
        }

        ~Thread() {
            LOG_TRACE("A Thread obj Destructor ", this);
        }

        void detach() { 
            assert(!started_);
            detach_ = true; 
        }

        void start() {
            LOG_TRACE("thread start");
            assert(!started_);
            auto p = this->shared_from_this();
            auto pp = new std::shared_ptr<Thread>(p) ;
            ::pthread_create(
                &id_, 
                NULL, 
                pthreadRunner, 
                (void*)pp);
            started_ = true;
        }

        void join() {
            assert(started_);
            ::pthread_join(id_, NULL);
        }

    private:
        static void* pthreadRunner(void* p) {
            LOG_TRACE("subthread run id = ", ::pthread_self());
            auto threadPP = (std::shared_ptr<Thread<Runable>>*)p;
            auto& thread = **threadPP;

            if(thread.detach_){
                ::pthread_detach(thread.id_);
            }
            thread.task_();

            delete threadPP;
            return NULL;
        }
    };
public:
    template<typename Runable>
    static std::shared_ptr<Thread<Runable>> Create(const Runable& task) {
        return std::make_shared<Thread<Runable>>(task);
    }

    static pthread_t currentThreadId() { return ::pthread_self(); }
};


    
} // namespace LGG
