#pragma once

#include "ConnectionSocket.h"
#include "StaticClass.h"
#include "SocketAPI.h"

namespace LGG
{

class ClientSocket : StaticClass {
public:

    struct ConnectionAndAddress {
        ConnectionSocket connection;
        SocketAddr address;
    };

    static ConnectionAndAddress connect(std::string_view addrStr, int port);
};

} // namespace LGG