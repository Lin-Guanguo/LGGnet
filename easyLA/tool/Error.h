#pragma once

#include "StaticClass.h"
#include "Format.h"
#include <errno.h>
#include <string.h>

namespace LGG 
{

class ErrorAPI : StaticClass {
public:
	static char* errnoMessage(int _errno) {
		return ::strerror(_errno);
	}
	
	static char* errnoMessage() {
		return ::strerror(errno);
	}

	static std::string reportErrno(int _errno) {
		return Format::concatToString(" errno = ", _errno, " message = ", errnoMessage(_errno));
	}
	
	static std::string reportErrno() {
		return reportErrno(errno);
	}


};



} // namespace LGG