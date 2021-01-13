#pragma once

#include "SocketAPI.h"
#include "Log.h"
#include "ConnectionSocket.h"

namespace LGG
{

class ClientSocket : StaticClass {
public:
    static ConnectionSocket connect(std::string_view addrStr, int port) {
        LOG_INFO("open clientSocket, server address = ", addrStr, ", port = ", port);
        int fd = SocketAPI::newSocket(AF_INET, SOCK_STREAM);
        SocketAddr addr(AF_INET, addrStr, port);
        SocketAPI::connect(fd, addr);
        return {fd, addr};
    }
};

} // namespace LGG