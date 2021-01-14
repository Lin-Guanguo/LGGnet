#pragma once

#include "Noncopyable.h"
#include "Buffer.h"
#include "SocketAPI.h"

namespace LGG
{

class ConnectionSocket : Noncopyable {
    //一直处于读模式
    Buffer buf_;
    int fd_;
    SocketAddr addr_;
    static size_t DEFAULT_BUFSIZE;
public:

    ConnectionSocket(int fd, SocketAddr addr) : fd_(fd), addr_(addr), buf_(DEFAULT_BUFSIZE) {
        buf_.readMode();
    };

    ~ConnectionSocket() { SocketAPI::close(fd_); };

    size_t readFd() {
        buf_.writeMode();
        auto res = buf_.putFromFd(fd_);
        buf_.readMode();
        return res;
    }

    std::string_view readLine() {
        std::string_view line;
        while((line = buf_.getLine()).size() == 0){
            readFd();
        }
        return line;
    }

    const SocketAddr& getAddr() const { return addr_; }

    void write(std::string_view str);

    void resizeBuf(size_t newSize) { buf_.resize(newSize); }

    static void setDEFAULT_BUFSIZE(size_t size) {
        DEFAULT_BUFSIZE = size;
    }

    static size_t getDEFAULT_BUFSIZE() {
        return DEFAULT_BUFSIZE;
    }
};

} // namespace LGG
