#include "Log.h"
#include "stdio.h"

using namespace LGG;

void defaultLogFun(std::string_view str){
    printf("%s", str.data());
}

LogSetting::LogLevel LogSetting::G_LOG_LEVEL = TRACE;
LogSetting::LogFunction LogSetting::G_LOG_FUNCTION = defaultLogFun ;

