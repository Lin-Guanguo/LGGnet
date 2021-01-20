#include "ServerSocket.h"
#include "Log.h"
#include "SocketAPI.h"
#include "IOAPI.h"
#include "Process.h"
#include "Log.h"
#include "ConnectionSocket.h"
#include "Thread.h"
#include "Buffer.h"
#include <unistd.h>
#include <string>

#include <stdbool.h>

using namespace std;
using namespace LGG;


int main(int argc, char** argv) {
    ServerSocket server(8011);
    int fd = server.getFd();

    char hello[] = "hello";
    int len = sizeof(hello);
    for (;;) {
        auto [connection, addr] = server.accept();
        LOG_INFO(addr.toString());
        auto t = Thread::Create([connection = std::move(connection)]() mutable {
            for (;;) {
                auto line = connection.readLine();
                if (line.size() == 0) break;
                connection.write("echo = ");
                connection.write(line);
                connection.flush();
            }
        });
        t->detach();
        t->start();
    }

}

