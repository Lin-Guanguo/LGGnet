#pragma once

#include "StaticClass.h"
#include <string_view>
#include <unistd.h>
#include <sys/uio.h>
#include "Log.h"
#include "Error.h"

namespace LGG
{

class IOAPI : StaticClass {
public:
	static auto read(int fd, char* buf, size_t nbytes) {
		auto readCount = ::read(fd, buf, nbytes);
		if (readCount < 0) {
			LOG_ERROR("readError return ", readCount , " ", ErrorAPI::errnoMessage(readCount));
		}
		return readCount;
	}

	static auto write(int fd, const char* buf, size_t nbytes) {
		return ::write(fd, buf, nbytes);
	}
	
	static auto write(int fd, const std::string_view& str) {
		return IOAPI::write(fd, str.data(), str.size());
	}
	
	template<typename... Strs>
	static auto writev(int fd, const Strs&... strs) {
		int iovcnt = sizeof...(strs);
		auto iov = new iovec[iovcnt]();
		int n = 0;
		(writevHelper(strs, iov, n), ...);
		auto res = ::writev(fd, iov, iovcnt);
		delete[] iov;
		return res;
	}

private:
	static void writevHelper(const std::string_view& str, iovec* iov, int& n) {
		iov[n].iov_base = const_cast<char*>(str.data());
		iov[n].iov_len = str.size();
		n++;
	}
	
};

} // namespcae LGG