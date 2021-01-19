#pragma once

#include "StaticClass.h"
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


};



} // namespace LGG