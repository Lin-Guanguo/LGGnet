#include "Buffer.h"
#include <stdlib.h>
#include <string.h>
#include "IOAPI.h"
#include <algorithm>
#include "Log.h"

using namespace std;
using namespace LGG;

Buffer::Buffer(size_t size){
    byteArray_ = (char*)::malloc(size * sizeof(char));
    if(byteArray_ == nullptr){
        LOG_FATAL("out of memory");
    }
    position_ = byteArray_;
    capital_ = byteArray_ + size;
    limit_ = capital_;
}

Buffer::~Buffer() {
    ::free(byteArray_);
}

void Buffer::resize(size_t size) {
    byteArray_ = (char*)::realloc(byteArray_ ,size * sizeof(char));
    if(byteArray_ == nullptr){
        LOG_FATAL("out of memory");
    }
    capital_ = byteArray_ + size;
    limit_ = capital_;
    position_ = byteArray_;
}

ssize_t Buffer::putFromFd(int fd) {
    auto remain = remainingSize();
    if(remain > 0){
        auto readCount = IOAPI::read(fd, position_, remain);
        position_ += readCount;
        return readCount;
    }else{
        return -1;
    }
}

ssize_t Buffer::getToFd(int fd, size_t maxBytes) {

}

void Buffer::compact() {
    mode_ = WRITE;
    ::memmove(byteArray_, position_, limit_ - position_);
    position_ = byteArray_ + (limit_ - position_);
    limit_ = capital_;
}

void Buffer::put(std::string_view src) {
    assert(mode_ == WRITE);
    ::mempcpy(position_, src.data(), src.size());
    position_ += src.size();
}

std::string_view Buffer::getLine() {
    assert(mode_ == READ);
    auto nl = std::find(position_, limit_, '\n');
    if(nl == limit_){
        return {};
    }else{
        return get(static_cast<size_t>(nl - position_ + 1));
    }
}