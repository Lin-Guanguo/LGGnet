#include "../../easyLA/tool/ServerSocket.h"
#include "../../easyLA/tool/Log.h"
#include <unistd.h>

using namespace std;
using namespace LGG;

int main(int argc, char** argv){
    ServerSocket server(8011);
    int fd = server.getFd();

    char hello[] = "hello";
    int len = sizeof(hello);
    for(;;){
        auto connection = server.accept();
        LOG_INFO(connection.getAddr().toStringAsIPV4());
        auto line = connection.readLine();
        connection.write(line);
    }
}