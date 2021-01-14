#pragma once

#include "Noncopyable.h"
#include <bits/unique_ptr.h>


namespace LGG
{
class Buffer;
class SocketAddr;

class ConnectionSocket : Noncopyable {
    std::unique_ptr<Buffer> readBuf_;
    std::unique_ptr<SocketAddr> addr_;
    int fd_;
    static size_t DEFAULT_BUFSIZE;
public:
    ConnectionSocket(int fd, SocketAddr addr);

    ~ConnectionSocket();

    size_t readFd();

    std::string_view readLine();

    const SocketAddr& getAddr() const { return *addr_; }

    void write(std::string_view str);

    void resizeBuf(size_t newSize);

    static void setDEFAULT_BUFSIZE(size_t size) {
        DEFAULT_BUFSIZE = size;
    }

    static size_t getDEFAULT_BUFSIZE() {
        return DEFAULT_BUFSIZE;
    }
};

} // namespace LGG
