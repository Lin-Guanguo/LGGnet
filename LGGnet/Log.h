#ifndef LGGNET_LOG
#define LGGNET_LOG

#include "StaticClass.h"
#include "Format.h"
#include "functional"
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
    using LogFunction = std::function<void(std::string_view)>;

    static void setG_LOG_LEVEL(LogLevel newLevel) { G_LOG_LEVEL = newLevel; }
    static LogLevel getG_LOG_LEVEL() { return G_LOG_LEVEL; }
    static LogFunction getG_LOG_FUNCTION() { return G_LOG_FUNCTION; }
    static void setG_LOG_FUNCTION(LogFunction fun) { G_LOG_FUNCTION = fun; }

  private:
    static LogLevel G_LOG_LEVEL;
    static LogFunction G_LOG_FUNCTION;
};


#define LGG_LOG_DEFINE_TEMPLATE(LOGLEVEL, LEVEL_NAME, ...) { \
    if(LGG::LogSetting::getG_LOG_LEVEL() <= LGG::LogSetting::LOGLEVEL) \
        LGG::LogSetting::getG_LOG_FUNCTION()(LGG::Format::concatToString(LEVEL_NAME, " file=", __FILE__, ", line=", __LINE__ , ": ", __VA_ARGS__, "\n"));}

#define LOG_TRACE(...) LGG_LOG_DEFINE_TEMPLATE(TRACE, "TRACE", __VA_ARGS__)
#define LOG_DEBUG(...) LGG_LOG_DEFINE_TEMPLATE(DEBUG, "DEBUG", __VA_ARGS__)
#define LOG_INFO(...) LGG_LOG_DEFINE_TEMPLATE(INFO, "INFO ", __VA_ARGS__)
#define LOG_WARN(...) LGG_LOG_DEFINE_TEMPLATE(WARN, "WARN ", __VA_ARGS__)
#define LOG_ERROR(...) LGG_LOG_DEFINE_TEMPLATE(ERROR, "ERROR", __VA_ARGS__)
#define LOG_FATAL(...) LGG_LOG_DEFINE_TEMPLATE(FATAL, "FATAL",  __VA_ARGS__)

} // namespace LGG

#endif