#pragma once

#include "StaticClass.h"
#include <string.h>

namespace LGG 
{

class ErrorAPI : StaticClass {
public:
	static char* errnoMessage(int _errno) {
		return ::strerror(_errno);
	}


};



} // namespace LGG