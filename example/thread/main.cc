#include "../../easyLA/tool/Thread.h"
#include <unistd.h>
#include <string>

using namespace std;
using namespace LGG;

class A {
public:
    void operator()(){
        LOG_INFO("C oprator()");
        return;
    }

    A(){}

    A(const A& that){
        LOG_INFO("copy")
    }
};

int main(int argc, char** argv){
    auto t = Thread::Create([](){
        LOG_INFO("Hello");
        return true;
    });
    t->start();
    LOG_INFO("join return ", t->join());
    ::sleep(4);
}