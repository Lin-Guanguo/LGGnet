#pragma once

#include "SocketAPI.h"
#include "Log.h"

namespace LGG
{

class ClientSocket {
    int fd_;
public:
    ClientSocket(std::string_view addrStr, int port) {
        LOG_INFO("open clientSocket, server address = ", addrStr, ", port = ", port);
        fd_ = SocketAPI::newSocket(AF_INET, SOCK_STREAM);
        SocketAddr addr(AF_INET, addrStr, port);
        SocketAPI::connect(fd_, addr);
    };

    ~ClientSocket() {};

    int getFd() { return fd_; }
};

} // namespace LGG