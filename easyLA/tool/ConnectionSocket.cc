#include "ConnectionSocket.h"
#include <unistd.h>

using namespace LGG;

void ConnectionSocket::write(std::string_view str){
    ::write(fd_, str.data(), str.size());
}