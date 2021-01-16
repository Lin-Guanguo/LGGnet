#pragma once

#include "Noncopyable.h"
#include <memory>


namespace LGG
{
class Buffer;
class SocketAddr;

class ConnectionSocket : Noncopyable {
    //usually in readMode
    std::unique_ptr<Buffer> readBuf_;
    //usually in writeMode
    std::unique_ptr<Buffer> writeBuf_;
    std::unique_ptr<SocketAddr> addr_;
    int fd_;
    static size_t DEFAULT_BUFSIZE;
public:
    ConnectionSocket(int fd, SocketAddr addr);

    ~ConnectionSocket();

    ssize_t readFd();

    std::string_view readLine();

    const SocketAddr& getAddr() const { return *addr_; }

    ssize_t write(std::string_view str);

    ssize_t flush();
    ssize_t flush(size_t maxSize);

    ssize_t flush(std::string_view str);

    void resizeBuf(size_t newSize);

    static void setDEFAULT_BUFSIZE(size_t size) {
        DEFAULT_BUFSIZE = size;
    }

    static size_t getDEFAULT_BUFSIZE() {
        return DEFAULT_BUFSIZE;
    }
};

} // namespace LGG
