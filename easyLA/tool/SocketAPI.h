#pragma once

#include "StaticClass.h"
#include <netinet/in.h>
#include <string_view>


namespace LGG
{

class SocketAddr {
    ::sockaddr_storage addr_;
public:
    SocketAddr();

    SocketAddr(int family, std::string_view addr, unsigned short port);

    SocketAddr(const ::sockaddr_storage& addr);

    sockaddr* getPtr() { return (sockaddr*)&addr_; }
    const sockaddr* getPtr() const { return (const sockaddr*)&addr_; }

    sockaddr_in* getPtrAsIPV4() { return (sockaddr_in*)&addr_; }
    const sockaddr_in* getPtrAsIPV4() const { return (const sockaddr_in*)&addr_; }

    sockaddr_in6* getPtrAsIPV6() { return (sockaddr_in6*)&addr_; }
    const sockaddr_in6* getPtrAsIPV6() const { return (const sockaddr_in6*)&addr_; }

    socklen_t getLen() const { return sizeof(addr_); }

    std::string toStringAsIPV4() const;

    std::string toStringAsIPV6() const;

    std::string toString() const;

    //::inet_pton
    static void AddrPerformToNet(int family, const char* src, char* dest);
};
    
class SocketAPI : StaticClass {
public:
    static constexpr int DEFAULT_BACKLOG = 128;

    static int newSocket(int domain, int type);

    static int bind(int fd, const SocketAddr& addr);

    static int listen(int fd);

    struct AcceptRes {
        int fd;
        SocketAddr addr;
    };

    static AcceptRes accept(int fd);

    static int close(int fd);

    static int connect(int fd, const SocketAddr& addr);
};

} // namespace LGG
