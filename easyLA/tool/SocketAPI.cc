#include "SocketAPI.h"
#include "Log.h"
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace LGG;

SocketAddr::SocketAddr() {
    memset(&addr_, 0, sizeof(addr_));
}

SocketAddr::SocketAddr(int family, std::string_view addr, unsigned short port) : SocketAddr() {
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

SocketAddr::SocketAddr(const ::sockaddr_storage& addr) {
    memcpy(&addr_, &addr, sizeof(sockaddr_storage));
}

std::string SocketAddr::toStringAsIPV4() const {
    constexpr int bufsize = sizeof(sockaddr_storage);
    char buf[bufsize];
    auto p = this->getPtrAsIPV4();
    ::inet_ntop(AF_INET, (const void*)&p->sin_addr, buf, bufsize);
    return Format::concatToString(buf, ":", p->sin_port);
}

std::string SocketAddr::toStringAsIPV6() const {
    constexpr int bufsize = sizeof(sockaddr_storage);
    char buf[bufsize];
    auto p = this->getPtrAsIPV6();
    ::inet_ntop(AF_INET6, (const void*)&p->sin6_addr, buf, bufsize);
    return Format::concatToString(buf, ":", p->sin6_port);
}

std::string SocketAddr::toString() const { 
    switch(addr_.ss_family){
        case AF_INET:
            return toStringAsIPV4();
        case AF_INET6:
            return toStringAsIPV6();
        default:
            return "unkonwIPVersion";
    }
}

int SocketAPI::newSocket(int domain, int type){
    LOG_TRACE("new Socket")
    int fd = ::socket(domain, type, 0);
    return fd;
}

int SocketAPI::bind(int fd, const SocketAddr& addr){
    LOG_TRACE("bind")
    int res = ::bind(fd, addr.getPtr(), addr.getLen());
    return res;
}

int SocketAPI::listen(int fd){
    LOG_TRACE("listen")
    int res = ::listen(fd, DEFAULT_BACKLOG);
    return res;
}

SocketAPI::AcceptRes SocketAPI::accept(int fd){
    LOG_TRACE("accept")
    AcceptRes res;
    socklen_t len;
    res.fd = ::accept(fd, res.addr.getPtr(), &len);
    return res;
}

int SocketAPI::close(int fd){
    LOG_TRACE("close")
    int res = ::close(fd);
    return res;
}

int SocketAPI::connect(int fd, const SocketAddr& addr){
    LOG_TRACE("connection")
    int res = ::connect(fd, addr.getPtr(), addr.getLen());
    return res;
}