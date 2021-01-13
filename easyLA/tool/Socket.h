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

namespace LGG
{

struct SocketAddr {
    SocketAddr();

    SocketAddr(std::string_view addr, unsigned short port){
        addr_.sin_family = AF_INET;
        ::inet_pton(AF_INET, addr.data(), &addr_.sin_addr);
        addr_.sin_port = ::htons(port);
    }

    SocketAddr(const sockaddr_storage* addr){
        if(((sockaddr*)addr)->sa_family != AF_INET){
            LOG_FATAL_AND_DIE("connecion TYPE WRONG ", (int)((sockaddr*)addr)->sa_family);
        }
        auto ipv4 = (const sockaddr_in*)addr;
        addr_.sin_family = AF_INET;
        addr_.sin_addr = ipv4->sin_addr;
        addr_.sin_port = ipv4->sin_port;
    }

    sockaddr* getPtr() { return (sockaddr*)&addr_; }
    const sockaddr* getPtr() const { return (const sockaddr*)&addr_; }

    socklen_t getLen() const { return sizeof(addr_); }

    std::string tostring() const { 
        assert(addr_.sin_family == AF_INET);
        char p[100];
        ::inet_ntop(AF_INET, (const void*)&addr_.sin_addr, p, 100);
        return Format::concatToString(p, ":", (int)addr_.sin_port);
    }

  private:
    ::sockaddr_in addr_;
};
    
class SocketOps : StaticClass {
  public:
    static constexpr int DEFAULT_BACKLOG = 128;

    static int newTCPSocket(){
        int fd = ::socket(AF_INET, SOCK_STREAM, 0);
        return fd;
    }

    static int newUDPSocket(){
        int fd = ::socket(AF_INET, SOCK_DGRAM, 0);
        return fd;
    }

    static int bind(int fd, const SocketAddr& addr){
        int res = ::bind(fd, addr.getPtr(), addr.getLen());
        return res;
    }

    static int listen(int fd){
        int res = ::listen(fd, DEFAULT_BACKLOG);
        return res;
    }

    struct acceptRes {
        int fd;
        SocketAddr addr;
    };

    static acceptRes accept(int fd){
        sockaddr_storage addr;
        socklen_t len;
        int clientfd = ::accept(fd, (sockaddr*)&addr, &len);
        return {clientfd, &addr};
    }

    static int close(int fd){
        int res = ::close(fd);
        return res;
    }

    static int connect(int fd, const SocketAddr& addr){
        int res = ::connect(fd, addr.getPtr(), addr.getLen());
        return res;
    }
};

} // namespace LGG
