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

SocketAddr::SocketAddr(sa_family_t family, std::string_view addr, unsigned short port) : SocketAddr() {
    setFamily(family);
    setAddress(addr);
    setPort(port);
}

SocketAddr::SocketAddr(const ::sockaddr_storage& addr) {
    memcpy(&addr_, &addr, sizeof(sockaddr_storage));
    setFamily(addr.ss_family);
}

SocketAddr::SocketAddr(const SocketAddr& that) {
    memcpy(&addr_, &that.addr_, sizeof(sockaddr_storage));
    len_ = that.len_;
}

void SocketAddr::setFamily(sa_family_t family) {
    addr_.ss_family = family;
    switch (family) {
    case AF_INET:
        len_ = sizeof(sockaddr_in);
        break;
    case AF_INET6:
        len_ = sizeof(sockaddr_in6);
        break;
    default:
        LOG_WARN("unkonw family used, can't init socklen");
    }
}

void SocketAddr::setAddress(std::string_view addr) {
    switch (getFamily()) {
        case AF_INET: {
            auto p = this->getPtrAsIPV4();
            AddrPerformToNet(AF_INET, addr.data(), &p->sin_addr);
        } break;
        case AF_INET6: {
            auto p = this->getPtrAsIPV6();
            AddrPerformToNet(AF_INET6, addr.data(), &p->sin6_addr);
        } break;
        default:
            LOG_WARN("unkonw family used, can't setAddress");
    }
}

void SocketAddr::setPort(unsigned short port) {
    switch (getFamily()){
        case AF_INET: {
            auto p = this->getPtrAsIPV4();
            p->sin_port = ::htons(port);
            len_ = sizeof(sockaddr_in);
        } break;
        case AF_INET6: {
            auto p = this->getPtrAsIPV6();
            p->sin6_port = ::htons(port);
            len_ = sizeof(sockaddr_in6);
        } break;
        default:
            LOG_WARN("unkonw family used, can't setport");
    }
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
    switch(getFamily()){
        case AF_INET:
            return toStringAsIPV4();
        case AF_INET6:
            return toStringAsIPV6();
        default:
            return "unkonw family used, can't toString";
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

SocketAPI::FdAndAddress SocketAPI::accept(int fd){
    LOG_TRACE("accept")
    FdAndAddress res;
    res.fd = ::accept(fd, res.addr.getPtr(), &res.addr.getLen());
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