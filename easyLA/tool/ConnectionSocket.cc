#include "ConnectionSocket.h"
#include "Buffer.h"
#include "SocketAPI.h"
#include "Log.h"
#include "IOAPI.h"
#include <unistd.h>

using namespace LGG;
using namespace std;

size_t ConnectionSocket::DEFAULT_READ_BUFSIZE = 1<<12;
size_t ConnectionSocket::DEFAULT_WRITE_BUFSIZE = 1<<12;

ConnectionSocket::ConnectionSocket(int fd, size_t readBufSize, size_t writeBufSize)
    : fd_(fd), 
    readBuf_(make_unique<Buffer>(readBufSize)),
    writeBuf_(make_unique<Buffer>(writeBufSize))
{
    readBuf_->readMode();
    writeBuf_->writeMode();
};

ConnectionSocket::ConnectionSocket(ConnectionSocket&& that)
    : readBuf_(std::move(that.readBuf_)),
    writeBuf_(std::move(that.writeBuf_)),
    fd_(that.fd_)
{
    //LOG_TRACE("ConnectionSocket move this = ", this)
    that.fd_ = -1;
}

ConnectionSocket::~ConnectionSocket() { 
    if (fd_ < 0)
        return;
    SocketAPI::close(fd_); 
};

ssize_t ConnectionSocket::readFd() {
    readBuf_->writeMode();
    auto res = readBuf_->putFromFd(fd_);
    readBuf_->readMode();
    return res;
}

std::string_view ConnectionSocket::readLine() {
    std::string_view line;
    while((line = readBuf_->getLine()).size() == 0){
        if( readFd() <= 0) break;
    }
    return line;
}

void ConnectionSocket::resizeReadBuf(size_t newSize) { readBuf_->resize(newSize); }
void ConnectionSocket::resizeWriteBuf(size_t newSize) { writeBuf_->resize(newSize); }

ssize_t ConnectionSocket::write(std::string_view str){
    LOG_TRACE("connection ", this, " write buf put ", str);
    return writeBuf_->put(str);
}

ssize_t ConnectionSocket::flush() {
    writeBuf_->readMode();
    auto res = writeBuf_->getToFd(fd_);
    writeBuf_->writeMode();
    return res;
}

ssize_t ConnectionSocket::flush(size_t maxSize) {
    writeBuf_->readMode();
    auto res = readBuf_->getToFd(fd_, maxSize);
    writeBuf_->writeMode();
    return res;
}

void ConnectionSocket::clearWriteBuf() {
    writeBuf_->clear();
}

