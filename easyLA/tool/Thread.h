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
        using TaskReturnType = decltype(task_());

        //task's return value's type could only be basetype or pointer
        ThreadHandle(Runable task) : task_(std::move(task)) {
            LOG_TRACE("A Thread obj Constructor ", this, " returnType is ", typeid(TaskReturnType).name());
            static_assert(std::is_pointer<TaskReturnType>::value || 
                    std::is_integral<TaskReturnType>::value || 
                    std::is_floating_point<TaskReturnType>::value);
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

        TaskReturnType join() {
            LOG_TRACE("join id = ", ::pthread_self());
            assert(started_);
            void* res;
            ::pthread_join(id_, &res);
            return *reinterpret_cast<TaskReturnType*>(&res);
        }

    private:
        static void* pthreadRunner(void* p) {
            LOG_TRACE("subthread run id = ", ::pthread_self());
            auto threadPP = (std::shared_ptr<ThreadHandle<Runable>>*)p;
            auto& thread = **threadPP;
            if(thread.detach_){
                ::pthread_detach(thread.id_);
            }
            TaskReturnType res = thread.task_();
            delete threadPP;
            return *reinterpret_cast<void**>(&res);
        }
    };
public:
    template<typename Runable>
    static std::shared_ptr<ThreadHandle<Runable>> Create(const Runable& task) {
        return std::make_shared<ThreadHandle<Runable>>(task);
    }

    static pthread_t currentThreadId() { return ::pthread_self(); }
};


    
} // namespace LGG
