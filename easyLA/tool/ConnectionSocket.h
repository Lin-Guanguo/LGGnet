#pragma once

#include "Noncopyable.h"
#include "Buffer.h"
#include "SocketAPI.h"

namespace LGG
{

class ConnectionSocket : Noncopyable {
    Buffer buf_;
    int fd_;
    SocketAddr addr_;
    static size_t DEFAULT_BUFSIZE;
public:

    ConnectionSocket(int fd, SocketAddr addr) : fd_(fd), addr_(addr), buf_(DEFAULT_BUFSIZE) {};

    ~ConnectionSocket() { SocketAPI::close(fd_); };

    Buffer& getBuffer() { return buf_; }

    void resizeBuf(size_t newSize) { buf_.resize(newSize); }

    const SocketAddr& getAddr() const { return addr_; }

    

    void write(std::string_view str);

    static void setDEFAULT_BUFSIZE(size_t size) {
        DEFAULT_BUFSIZE = size;
    }

    static size_t getDEFAULT_BUFSIZE() {
        return DEFAULT_BUFSIZE;
    }
};

} // namespace LGG
