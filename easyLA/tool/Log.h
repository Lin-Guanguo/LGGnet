#pragma once

#include "StaticClass.h"
#include "Format.h"
#include <string_view>

namespace LGG
{

class LogSetting : StaticClass {
public:
    enum LogLevel{
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        NUM_LOG_LEVELS,
    };
    using LogFunction = void(*)(std::string_view);

    static void setG_LOG_LEVEL(LogLevel newLevel) { G_LOG_LEVEL = newLevel; }
    static LogLevel getG_LOG_LEVEL() { return G_LOG_LEVEL; }
    static void setG_LOG_FUNCTION(LogFunction fun) { G_LOG_FUNCTION = fun; }
    static LogFunction getG_LOG_FUNCTION() { return G_LOG_FUNCTION; }

    static void defaultLogFun(std::string_view str){
        fprintf(stderr ,"%s", str.data());
    }
private:
    static LogLevel G_LOG_LEVEL;
    static LogFunction G_LOG_FUNCTION;
};

inline LogSetting::LogLevel LogSetting::G_LOG_LEVEL = TRACE;
inline LogSetting::LogFunction LogSetting::G_LOG_FUNCTION = defaultLogFun ;


#ifndef LOG_CLOSE
    #define LGG_LOG_DEFINE_TEMPLATE(LOGLEVEL, LEVEL_NAME, ...) { \
        if(LGG::LogSetting::getG_LOG_LEVEL() <= LGG::LogSetting::LOGLEVEL) \
            LGG::LogSetting::getG_LOG_FUNCTION()(LGG::Format::concatToString(LEVEL_NAME, " file=", __FILE__, ", line=", __LINE__ , ": ", __VA_ARGS__, "\n"));}
            
    #define LOG_TRACE(...) LGG_LOG_DEFINE_TEMPLATE(TRACE, "TRACE", __VA_ARGS__)
    #define LOG_DEBUG(...) LGG_LOG_DEFINE_TEMPLATE(DEBUG, "DEBUG", __VA_ARGS__)
    #define LOG_INFO(...) LGG_LOG_DEFINE_TEMPLATE(INFO, "INFO ", __VA_ARGS__)
    #define LOG_WARN(...) LGG_LOG_DEFINE_TEMPLATE(WARN, "WARN ", __VA_ARGS__)
    #define LOG_ERROR(...) LGG_LOG_DEFINE_TEMPLATE(ERROR, "ERROR", __VA_ARGS__)
    #define LOG_FATAL(...) { LGG_LOG_DEFINE_TEMPLATE(FATAL, "FATAL",  __VA_ARGS__); exit(-1); }
#else
    #define LOG_TRACE(...) {}
    #define LOG_DEBUG(...) {}
    #define LOG_INFO(...) {}
    #define LOG_WARN(...) {}
    #define LOG_ERROR(...) {}
    #define LOG_FATAL(...) {}
#endif

} // namespace LGG
