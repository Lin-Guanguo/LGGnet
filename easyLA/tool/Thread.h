#pragma once

#include "StaticClass.h"
#include "Noncopyable.h"
#include "Log.h"
#include <type_traits>
#include <pthread.h>
#include <memory>
#include <cassert>

namespace LGG
{

class Thread : StaticClass {
private:
    template<typename Runable>
    class ThreadHandle : Noncopyable, public std::enable_shared_from_this<ThreadHandle<Runable>> {
    private:
        pthread_t id_;
        Runable task_;
        volatile bool detach_ = false;
        volatile bool started_ = false;
    public:
        ThreadHandle(Runable&& task) : task_(std::move(task)) {
            LOG_TRACE("A Thread obj Constructor ");
        }

        ~ThreadHandle() {
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
            auto pp = new std::shared_ptr<ThreadHandle>(p) ;
            ::pthread_create(
                &id_, 
                NULL, 
                pthreadRunner, 
                (void*)pp);
            started_ = true;
        }

        void join() {
            LOG_TRACE("join threadobj = ", this);
            assert(started_);
            ::pthread_join(id_, NULL);
            return;
        }

    private:
        static void* pthreadRunner(void* p) {
            LOG_TRACE("subthread run threadid = ", ::pthread_self());
            auto threadPP = (std::shared_ptr<ThreadHandle<Runable>>*)p;
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
    static std::shared_ptr<ThreadHandle<Runable>> Create(Runable&& task) {
        return std::make_shared<ThreadHandle<Runable>>(std::forward<Runable>(task));
    }

    static pthread_t currentThreadId() { return ::pthread_self(); }
};


    
} // namespace LGG
