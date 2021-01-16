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
    static size_t DEFAULT_READ_BUFSIZE;
    static size_t DEFAULT_WRITE_BUFSIZE;
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

    void resizeReadBuf(size_t newSize);

    void resizeWriteBuf(size_t newSize);

    static void setDEFAULT_READ_BUFSIZE(size_t size) {
        DEFAULT_READ_BUFSIZE = size;
    }

    static size_t getDEFAULT_READ_BUFSIZE() {
        return DEFAULT_READ_BUFSIZE;
    }
    
    static void setDEFAULT_WRITE_BUFSIZE(size_t size) {
        DEFAULT_WRITE_BUFSIZE = size;
    }

    static size_t getDEFAULT_WRITE_BUFSIZE() {
        return DEFAULT_WRITE_BUFSIZE;
    }
};

} // namespace LGG
