#include "ServerSocket.h"
#include "Log.h"
#include "SocketAPI.h"
#include "IOAPI.h"
#include <unistd.h>
#include <string>

using namespace std;
using namespace LGG;

int main(int argc, char** argv) {
    ServerSocket server(8011);
    int fd = server.getFd();

    ConnectionSocket::setDEFAULT_BUFSIZE(10);

    char hello[] = "hello";
    int len = sizeof(hello);
    for (;;) {
        auto connection = server.accept();
        LOG_INFO(connection.getAddr().toStringAsIPV4());
        auto line = connection.readLine();
    }
}