#include "SocketAPI.h"
#include "Error.h"
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
                AddrPerformToNet(AF_INET, addr.data(), &p->sin_addr);
                p->sin_port = ::htons(port);
            }
                break;
            case AF_INET6:{
                auto p = this->getPtrAsIPV6();
                AddrPerformToNet(AF_INET6, addr.data(), &p->sin6_addr);
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
    AddrNetToPerform(AF_INET, (const void*)&p->sin_addr, buf, bufsize);
    return Format::concatToString(buf, ":", p->sin_port);
}

std::string SocketAddr::toStringAsIPV6() const {
    constexpr int bufsize = sizeof(sockaddr_storage);
    char buf[bufsize];
    auto p = this->getPtrAsIPV6();
    AddrNetToPerform(AF_INET6, (const void*)&p->sin6_addr, buf, bufsize);
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

void SocketAddr::AddrPerformToNet(int family, const char* src, void* dest) {
    auto res = ::inet_pton(family, src, dest);
    if (res == 0)
        LOG_ERROR("src does not  contain a character string representing a valid network address in the specified address family")
    else if (res < 0)
        LOG_ERROR("::inet_pton error return ", res, ErrorAPI::reportErrno());
}

void SocketAddr::AddrNetToPerform(int family, const void* src, char* dest, socklen_t len) {
    auto res = ::inet_ntop(family, src, dest, len);
    if (res == 0)
        LOG_ERROR("src does not  contain a character string representing a valid network address in the specified address family")
    else if (res < 0)
        LOG_ERROR("::inet_ntop error return ", res, ErrorAPI::reportErrno());
}

int SocketAPI::newSocket(int domain, int type){
    LOG_TRACE("new Socket")
    int fd = ::socket(domain, type, 0);
    if (fd < 0) LOG_ERROR("SocketAPI::newSocket error return ", fd, ErrorAPI::reportErrno());
    return fd;
}

int SocketAPI::bind(int fd, const SocketAddr& addr){
    LOG_TRACE("bind")
    int res = ::bind(fd, addr.getPtr(), addr.getLen());
    if (res < 0) LOG_ERROR("SocketAPI::bind error return ", res, ErrorAPI::reportErrno());
    return res;
}

int SocketAPI::listen(int fd){
    LOG_TRACE("listen")
    int res = ::listen(fd, DEFAULT_BACKLOG);
    if (res < 0) LOG_ERROR("SocketAPI::listen error return ", res, ErrorAPI::reportErrno());
    return res;
}

SocketAPI::AcceptRes SocketAPI::accept(int fd){
    LOG_TRACE("accept")
    AcceptRes res;
    socklen_t len;
    res.fd = ::accept(fd, res.addr.getPtr(), &len);
    if (res.fd < 0) LOG_ERROR("SocketAPI::accept error return ", res.fd, ErrorAPI::reportErrno());
    return res;
}

int SocketAPI::close(int fd){
    LOG_TRACE("close")
    int res = ::close(fd);
    if (res < 0) LOG_ERROR("SocketAPI::close error return ", res, ErrorAPI::reportErrno());
    return res;
}

int SocketAPI::connect(int fd, const SocketAddr& addr){
    LOG_TRACE("connection")
    int res = ::connect(fd, addr.getPtr(), addr.getLen());
    if (res < 0) LOG_ERROR("SocketAPI::connect error return ", res, ErrorAPI::reportErrno());
    return res;
}