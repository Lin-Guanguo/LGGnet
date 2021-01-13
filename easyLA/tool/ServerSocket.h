#pragma once

#include "SocketAPI.h"
#include "ClientSocket.h"
#include "Log.h"
#include "ConnectionSocket.h"

namespace LGG
{

class ServerSocket : Noncopyable {
    int fd_;
public:
    ServerSocket(int port) {
        LOG_INFO("open serverSocket, port = ", port);
        fd_ = SocketAPI::newSocket(AF_INET, SOCK_STREAM);
        SocketAddr addr(AF_INET, "127.0.0.1", port);
        SocketAPI::bind(fd_, addr);
        SocketAPI::listen(fd_);
    };

    ~ServerSocket() { SocketAPI::close(fd_); };

    ConnectionSocket accept() { 
        auto acceptRes = SocketAPI::accept(fd_); 
        return {acceptRes.fd, acceptRes.addr};
    }

    int getFd() { return fd_; }
};



} // namespace LGG

