#pragma once

#include "StaticClass.h"
#include <netinet/in.h>
#include <string_view>


namespace LGG
{

class SocketAddr {
    ::sockaddr_storage addr_;
    socklen_t len_;
public:
    SocketAddr();

    SocketAddr(sa_family_t family, std::string_view addr, unsigned short port);

    SocketAddr(const ::sockaddr_storage& addr);

    SocketAddr(const SocketAddr& that);

    void setFamily(sa_family_t family);

    void setAddress(std::string_view addr);

    void setPort(unsigned short port);

    sockaddr* getPtr() { return (sockaddr*)&addr_; }
    const sockaddr* getPtr() const { return (const sockaddr*)&addr_; }

    sockaddr_in* getPtrAsIPV4() { return (sockaddr_in*)&addr_; }
    const sockaddr_in* getPtrAsIPV4() const { return (const sockaddr_in*)&addr_; }

    sockaddr_in6* getPtrAsIPV6() { return (sockaddr_in6*)&addr_; }
    const sockaddr_in6* getPtrAsIPV6() const { return (const sockaddr_in6*)&addr_; }

    auto getFamily() const { return addr_.ss_family; }

    socklen_t& getLen() { return len_; };
    socklen_t getLen() const { return len_; };


    std::string toStringAsIPV4() const;

    std::string toStringAsIPV6() const;

    std::string toString() const;

    //::inet_pton
    static void AddrPerformToNet(int family, const char* src, void* dest);
    
    //::inet_ntop
    static void AddrNetToPerform(int family, const void* src, char* dest, socklen_t len);

};
    
class SocketAPI : StaticClass {
public:
    static constexpr int DEFAULT_BACKLOG = 128;

    static int newSocket(int domain, int type);

    static int bind(int fd, const SocketAddr& addr);

    static int listen(int fd);

    struct FdAndAddress {
        int fd;
        SocketAddr addr;
    };

    static FdAndAddress accept(int fd);

    static int close(int fd);

    static int connect(int fd, const SocketAddr& addr);
};

} // namespace LGG
