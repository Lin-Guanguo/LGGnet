#pragma once

#include "Noncopyable.h"
#include <memory>


namespace LGG
{
class Buffer;

class ConnectionSocket : Noncopyable {
    //usually in readMode
    std::unique_ptr<Buffer> readBuf_;
    //usually in writeMode
    std::unique_ptr<Buffer> writeBuf_;
    int fd_;
    static size_t DEFAULT_READ_BUFSIZE;
    static size_t DEFAULT_WRITE_BUFSIZE;
public:
    ConnectionSocket(int fd) : ConnectionSocket(fd, DEFAULT_READ_BUFSIZE, DEFAULT_WRITE_BUFSIZE) {};

    ConnectionSocket(int fd, size_t readBufSize, size_t writeBufSize);

    //会自动进行依次flush();
    ~ConnectionSocket();

    //读取文件描述符，将内容存到readBuf内
    ssize_t readFd();

    std::string_view readLine();

    //将信息写入缓存，写入文件描述符还需要依次flush
    ssize_t write(std::string_view str);

    //将写入缓存的内容写到绑定的文件描述符内
    ssize_t flush();
    //将写入缓存的内容写到绑定的文件描述符内
    ssize_t flush(size_t maxSize);

    //flush with a additional string
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
