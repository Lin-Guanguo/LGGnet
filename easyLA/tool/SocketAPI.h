#pragma once

#include "StaticClass.h"
#include "Log.h"
#include <unistd.h>
#include <cassert>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string_view>
#include <string>
#include <string.h>

namespace LGG
{

class SocketAddr {
    ::sockaddr_storage addr_;
  public:
    SocketAddr() {};

    SocketAddr(int family, std::string_view addr, unsigned short port){
        this->getPtr()->sa_family = family;
        switch(family){
            case AF_INET:{
                auto p = this->getPtrAsIPV4();
                ::inet_pton(AF_INET, addr.data(), &p->sin_addr);
                p->sin_port = ::htons(port);
            }
                break;
            case AF_INET6:{
                auto p = this->getPtrAsIPV6();
                ::inet_pton(AF_INET6, addr.data(), &p->sin6_addr);
                p->sin6_port = ::htons(port);
            }
                break;
            default:
                LOG_WARN("unkonw domain used, can't init");
        }
        LOG_TRACE("new Socket Addr, domain = ", family);
    }

    SocketAddr(const ::sockaddr_storage& addr){
        memcpy(&addr_, &addr, sizeof(sockaddr_storage));
    }

    sockaddr* getPtr() { return (sockaddr*)&addr_; }
    const sockaddr* getPtr() const { return (const sockaddr*)&addr_; }

    sockaddr_in* getPtrAsIPV4() { return (sockaddr_in*)&addr_; }
    const sockaddr_in* getPtrAsIPV4() const { return (const sockaddr_in*)&addr_; }

    sockaddr_in6* getPtrAsIPV6() { return (sockaddr_in6*)&addr_; }
    const sockaddr_in6* getPtrAsIPV6() const { return (const sockaddr_in6*)&addr_; }

    socklen_t getLen() const { return sizeof(addr_); }

    std::string toStringAsIPV4() const {
        constexpr int bufsize = sizeof(sockaddr_storage);
        char buf[bufsize];
        auto p = this->getPtrAsIPV4();
        ::inet_ntop(AF_INET, (const void*)&p->sin_addr, buf, bufsize);
        return Format::concatToString(buf, ":", p->sin_port);
    }

    std::string toStringAsIPV6() const {
        constexpr int bufsize = sizeof(sockaddr_storage);
        char buf[bufsize];
        auto p = this->getPtrAsIPV6();
        ::inet_ntop(AF_INET6, (const void*)&p->sin6_addr, buf, bufsize);
        return Format::concatToString(buf, ":", p->sin6_port);
    }

    std::string toString() const { 
        switch(addr_.ss_family){
            case AF_INET:
                return toStringAsIPV4();
            case AF_INET6:
                return toStringAsIPV6();
            default:
                return "unkonwIPVersion";
        }
    }

};
    
class SocketAPI : StaticClass {
  public:
    static constexpr int DEFAULT_BACKLOG = 128;

    static int newSocket(int domain, int type){
        LOG_TRACE("new Socket")
        int fd = ::socket(domain, type, 0);
        return fd;
    }

    static int bind(int fd, const SocketAddr& addr){
        LOG_TRACE("bind")
        int res = ::bind(fd, addr.getPtr(), addr.getLen());
        return res;
    }

    static int listen(int fd){
        LOG_TRACE("listen")
        int res = ::listen(fd, DEFAULT_BACKLOG);
        return res;
    }

    struct acceptRes {
        int fd;
        SocketAddr addr;
    };

    static acceptRes accept(int fd){
        LOG_TRACE("accept")
        acceptRes res;
        socklen_t len;
        res.fd = ::accept(fd, res.addr.getPtr(), &len);
        return res;
    }

    static int close(int fd){
        LOG_TRACE("close")
        int res = ::close(fd);
        return res;
    }

    static int connect(int fd, const SocketAddr& addr){
        LOG_TRACE("connection")
        int res = ::connect(fd, addr.getPtr(), addr.getLen());
        return res;
    }
};

} // namespace LGG
