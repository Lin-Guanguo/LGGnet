#include "ClientSocket.h"
#include "SocketAPI.h"
#include "Log.h"

using namespace LGG;

ClientSocket::ConnectionAndAddress ClientSocket::connect(std::string_view addrStr, int port) {
    LOG_INFO("open clientSocket, server address = ", addrStr, ", port = ", port);
    int fd = SocketAPI::newSocket(AF_INET, SOCK_STREAM);
    SocketAddr addr(AF_INET, addrStr, port);
    SocketAPI::connect(fd, addr);
    return {fd, addr};
}