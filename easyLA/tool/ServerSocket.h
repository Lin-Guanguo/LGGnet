#pragma once

#include "ConnectionSocket.h"
#include "SocketAPI.h"

namespace LGG
{

class ServerSocket : Noncopyable {
    int fd_;
public:
    ServerSocket(int port);

    ~ServerSocket();

    struct ConnectionAndAddress {
        ConnectionSocket connection;
        SocketAddr address;
    };

    ConnectionAndAddress accept();

    SocketAPI::FdAndAddress acceptFd();

    int getFd() { return fd_; }
};



} // namespace LGG

