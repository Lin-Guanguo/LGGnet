#pragma once

#include "StaticClass.h"
#include "Noncopyable.h"
#include "Log.h"
#include <pthread.h>
#include <memory>
#include <cassert>

namespace LGG
{

class CurrentThread : StaticClass {
public:
    static pthread_t threadId() { return ::pthread_self(); }
};

// template<typename Runable>
// class Thread : Noncopyable {
// private:
//     pthread_t id_;
//     Runable* task_;
//     bool detach_ = false;
//     volatile bool started_ = false;
// public:
//     Thread(const Runable& runable) {
//         auto task_ = (void*)new Runable(runable);
//     }

//     ~Thread() {
//         if( !started_ ) delete task_;
//     }

//     void detach() { 
//         assert(!started_);
//         detach_ = true; 
//     }

//     void start() {
//         assert(!started_);
//         ::pthread_create(&id_, NULL, 
//             pthreadRunner, 
//             (void*)task_);
//         started_ = true;
//     }

//     void join() {
//         assert(started_);
//         ::pthread_join(id_, NULL);
//     }

// private:


//     void* pthreadRunner(void* p) {
//         LOG_TRACE("sub thread run id = ", ::pthread_self());
//         if(detach_){
//             ::pthread_detach(id_);
//         }
//         auto prunable = (Runable*)p;
//         (*prunable)();
//         delete prunable;
//         return NULL;
//     }
// };
    
} // namespace LGG
