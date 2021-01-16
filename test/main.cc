#include "Log.h"
#include "ServerSocket.h"
#include "SocketAPI.h"

using namespace LGG;

int main() {
    ServerSocket server(8011);
    int fd = server.getFd();

    char hello[] = "hello";
    int len = sizeof(hello);
    for (;;) {
        auto connection = server.accept();
        LOG_INFO(connection.getAddr().toStringAsIPV4());
        auto line = connection.readLine();
        connection.write(line);
    }
}