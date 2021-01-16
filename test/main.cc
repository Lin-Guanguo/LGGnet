#include "Log.h"
#include "Error.h"
#include "IOAPI.h"

using namespace LGG;

int main(int argc, char** argv) {
	auto p = IOAPI::read;
	LOG_INFO("hello");
	errno = -1;
	LOG_INFO(ErrorAPI::errnoMessage(errno));
	::perror("hello");
}