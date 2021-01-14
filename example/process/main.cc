#include "../../easyLA/tool/Log.h"
#include "../../easyLA/tool/Process.h"
#include <unistd.h>

using namespace std;
using namespace LGG;

int main(int argc, char** argv){
    Process::ForkAndRun([](){
        Process::ForkAndExecve("./helloworld", NULL, NULL);
    });
    LOG_INFO("main end pid = ", ::getpid());
}