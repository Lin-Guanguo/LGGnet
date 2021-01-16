#pragma once

#include "StaticClass.h"
#include <unistd.h>

namespace LGG
{

class IOAPI : StaticClass {
public:
	static auto read(int fd, char* buf, size_t nbytes) {
		return ::read(fd, buf, nbytes);
	}

	static auto write(int fd, char* buf, size_t nbytes) {
		return ::write(fd, buf, nbytes);
	}

};

} // namespcae LGG