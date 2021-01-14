#include "ServerSocket.h"
#include "SocketAPI.h"
#include "Log.h"

using namespace LGG;

ServerSocket::ServerSocket(int port) {
    LOG_INFO("open serverSocket, port = ", port);
    fd_ = SocketAPI::newSocket(AF_INET, SOCK_STREAM);
    SocketAddr addr(AF_INET, "127.0.0.1", port);
    SocketAPI::bind(fd_, addr);
    SocketAPI::listen(fd_);
};

ServerSocket::~ServerSocket() { SocketAPI::close(fd_); };

ConnectionSocket ServerSocket::accept() { 
    auto acceptRes = SocketAPI::accept(fd_); 
    return {acceptRes.fd, acceptRes.addr};
}