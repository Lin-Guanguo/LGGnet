#pragma once

#include "ConnectionSocket.h"

namespace LGG
{

class ServerSocket : Noncopyable {
    int fd_;
public:
    ServerSocket(int port);

    ~ServerSocket();

    ConnectionSocket accept();

    int getFd() { return fd_; }
};



} // namespace LGG

