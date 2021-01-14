#include "ConnectionSocket.h"
#include "SocketAPI.h"
#include <unistd.h>

using namespace LGG;

ConnectionSocket::~ConnectionSocket() { SocketAPI::close(fd_); };

ssize_t ConnectionSocket::readFromSocket() { return buf_.writeFromFd(fd_); }

std::string ConnectionSocket::readAllBuf() { return buf_.readAll(); }

std::string ConnectionSocket::read(ssize_t len) { 
    while(buf_.readableSize() < len){
        readFromSocket();
    }
    return buf_.read(len);
}

std::string ConnectionSocket::readLine(){
    std::string line = buf_.readLine();
    while(line.size() == 0){
        if(readFromSocket() == 0){
            return {};
        } 
        line = buf_.readLine();
    }
    return line;
}

std::string ConnectionSocket::seek(ssize_t len) {
    while(buf_.readableSize() < len){
        readFromSocket();
    }
    return buf_.seek(len);
}

auto ConnectionSocket::bufSize(){
    return buf_.readableSize();
}

void ConnectionSocket::write(std::string_view str);