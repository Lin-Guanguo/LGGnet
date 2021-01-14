#pragma once

#include "ConnectionSocket.h"

namespace LGG
{

class ClientSocket : StaticClass {
public:
    static ConnectionSocket connect(std::string_view addrStr, int port);
};

} // namespace LGG