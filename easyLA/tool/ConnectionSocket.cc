#include "ConnectionSocket.h"
#include "Buffer.h"
#include "SocketAPI.h"
#include <unistd.h>

using namespace LGG;
using namespace std;

size_t ConnectionSocket::DEFAULT_BUFSIZE = 1<<12;

ConnectionSocket::ConnectionSocket(int fd, SocketAddr addr) 
    : fd_(fd), 
    addr_(make_unique<SocketAddr>(addr)), 
    readBuf_(make_unique<Buffer>(DEFAULT_BUFSIZE)) 
{
    readBuf_->readMode();
};

ConnectionSocket::~ConnectionSocket() { SocketAPI::close(fd_); };

ssize_t ConnectionSocket::readFd() {
    readBuf_->writeMode();
    auto res = readBuf_->putFromFd(fd_);
    readBuf_->readMode();
    return res;
}

std::string_view ConnectionSocket::readLine() {
    std::string_view line;
    while((line = readBuf_->getLine()).size() == 0){
        readFd();
    }
    return line;
}

void ConnectionSocket::resizeBuf(size_t newSize) { readBuf_->resize(newSize); }

void ConnectionSocket::write(std::string_view str){
    ::write(fd_, str.data(), str.size());
}