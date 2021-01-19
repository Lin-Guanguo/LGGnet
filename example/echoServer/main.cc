#include "ServerSocket.h"
#include "Log.h"
#include "SocketAPI.h"
#include <unistd.h>
#include <string>

using namespace std;
using namespace LGG;

int main(int argc, char** argv) {
    ServerSocket server(8011);
    int fd = server.getFd();

    char hello[] = "hello";
    int len = sizeof(hello);
    for (;;) {
        auto [connection, addr] = server.accept();
        LOG_INFO(addr.toStringAsIPV4());
        auto line = connection.readLine();
        connection.write(line);
        connection.flush();
    }
}