#pragma once

#include "Noncopyable.h"
#include "Buffer.h"
#include "SocketAPI.h"
#include <unistd.h>

namespace LGG
{

class ConnectionSocket : Noncopyable {
    Buffer buf_;
    int fd_;
    SocketAddr addr_;
public:
    ConnectionSocket(int fd, SocketAddr addr) : fd_(fd), addr_(addr) {};

    ~ConnectionSocket() { SocketAPI::close(fd_); };

    std::string readAll() { return buf_.readAll(); }

    std::string read(size_t len) { 
        while(buf_.readableSize() < len){
            readFd();
        }
        return buf_.read(len);
    }

    std::string readLine(){
        std::string line = buf_.readLine();
        while(line.size() == 0){
            if(readFd() == 0){
                return {};
            } 
            line = buf_.readLine();
        }
        return line;
    }

    Buffer& getBuffer() { return buf_;}

    void write(std::string_view str){
        ::write(fd_, str.data(), str.size());
    }
    
private:
    ssize_t readFd() { return buf_.writeFromFd(fd_); }
};

} // namespace LGG
