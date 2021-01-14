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
public:
    ConnectionSocket(int fd, SocketAddr addr) : fd_(fd), addr_(addr) {};

    ~ConnectionSocket() { SocketAPI::close(fd_); };

    ssize_t readFromSocket() { return buf_.writeFromFd(fd_); }

    std::string readAllBuf() { return buf_.readAll(); }

    std::string read(ssize_t len) { 
        while(buf_.readableSize() < len){
            readFromSocket();
        }
        return buf_.read(len);
    }

    std::string readLine(){
        std::string line = buf_.readLine();
        while(line.size() == 0){
            if(readFromSocket() == 0){
                return {};
            } 
            line = buf_.readLine();
        }
        return line;
    }

    std::string seek(ssize_t len) {
        while(buf_.readableSize() < len){
            readFromSocket();
        }
        return buf_.seek(len);
    }

    auto bufSize(){
        return buf_.readableSize();
    }

    Buffer& getBuffer() { return buf_;}

    const SocketAddr& getAddr() const { return addr_; }

    void write(std::string_view str);
};

} // namespace LGG
