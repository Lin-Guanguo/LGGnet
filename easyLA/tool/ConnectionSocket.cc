#include "ConnectionSocket.h"
#include <unistd.h>

using namespace LGG;

size_t ConnectionSocket::DEFAULT_BUFSIZE = 1<<12;

void ConnectionSocket::write(std::string_view str){
    ::write(fd_, str.data(), str.size());
}