#pragma once

#include "StaticClass.h"
#include <sys/uio.h>
#include "Log.h"
#include "Error.h"

namespace LGG
{

class IOAPI : StaticClass {
public:
	static ssize_t read(int fd, char* buf, size_t nbytes);

	static ssize_t write(int fd, const char* buf, size_t nbytes);
	
	static ssize_t write(int fd, const std::string_view& str);
	
	template<typename... Strs>
	static ssize_t writev(int fd, const Strs&... strs) {
		int iovcnt = sizeof...(strs);
		auto iov = new iovec[iovcnt]();
		int n = 0;
		(writevHelper(strs, iov, n), ...);
		auto res = ::writev(fd, iov, iovcnt);
		if(res < 0)  LOG_WARN("writev error return ", res, " ", ErrorAPI::errnoMessage(errno));
		delete[] iov;
		return res;
	}

	static int close(int fd);

private:
	static void writevHelper(const std::string_view& str, iovec* iov, int& n);
};

} // namespcae LGG