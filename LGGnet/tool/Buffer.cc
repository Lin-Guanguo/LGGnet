#include "Buffer.h"
#include <unistd.h>

using namespace std;
using namespace LGG;

ssize_t Buffer::writefd(int fd) {
    char stackbuf[1<<16];
    auto readSize = ::read(fd, stackbuf, 1 << 16);
    LOG_TRACE("Buffer ", this, " read ", readSize, " from fd ", fd);
    if(readSize > 0){
        std::copy(stackbuf, stackbuf + readSize, std::back_insert_iterator(buf_));
    }
    return readSize;
}