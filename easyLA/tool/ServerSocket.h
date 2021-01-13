#pragma once

#include "SocketAPI.h"
#include "Log.h"

namespace LGG
{

class ServerSocket{
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

    auto accept() { return SocketAPI::accept(fd_); }

    int getFd() { return fd_; }
};



} // namespace LGG

