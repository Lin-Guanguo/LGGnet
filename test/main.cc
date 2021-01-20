#include "ServerSocket.h"
#include "Log.h"
#include "SocketAPI.h"
#include "IOAPI.h"
#include "Process.h"
#include "Log.h"
#include "ConnectionSocket.h"
#include "Thread.h"
#include <unistd.h>
#include <string>

#include <stdbool.h>

using namespace std;
using namespace LGG;


//int main(int argc, char** argv) {
//    ServerSocket server(8011);
//    int fd = server.getFd();
//
//    char hello[] = "hello";
//    int len = sizeof(hello);
//    for (;;) {
//        auto [connection, addr] = server.accept();
//        LOG_INFO(addr.toString());
//        auto line = connection.readLine();
//        connection.write(line);
//        connection.write(" ");
//        connection.write(addr.toStringAsIPV4());
//        connection.flush();
//    }
//
//}

int main(int argc, char** argv) {
    auto t = Thread::Create([]() {
        LOG_INFO("Hello");
        return;
        });
    t->start();
    t->join();
    LOG_INFO("join return ");
    ::sleep(4);
}