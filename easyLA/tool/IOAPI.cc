#include "IOAPI.h"
#include <unistd.h>
#include <string_view>

using namespace LGG;

ssize_t IOAPI::read(int fd, char* buf, size_t nbytes) {
	auto readCount = ::read(fd, buf, nbytes);
	if (readCount < 0) {
		LOG_ERROR("read error return ", readCount, ErrorAPI::reportErrno());
	}
	return readCount;
}

ssize_t IOAPI::write(int fd, const char* buf, size_t nbytes) {
	auto res = ::write(fd, buf, nbytes);
	if (res < 0) LOG_WARN("write error return ", res, ErrorAPI::reportErrno());
	return res;
}

ssize_t IOAPI::write(int fd, const std::string_view& str) {
	return IOAPI::write(fd, str.data(), str.size());
}

int IOAPI::close(int fd) {
	auto res = ::close(fd);
	if (res < 0) LOG_WARN("close error return ", res, ErrorAPI::reportErrno());
	return res;
}

void IOAPI::writevHelper(const std::string_view& str, iovec* iov, int& n) {
	iov[n].iov_base = const_cast<char*>(str.data());
	iov[n].iov_len = str.size();
	n++;
}