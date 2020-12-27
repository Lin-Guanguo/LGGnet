#ifndef LGGNET_LOG
#define LGGNET_LOG

#include "Noncopyable.h"
#include <iostream>

namespace LGG
{

typedef std::ostream Ostream;   //暂时工程

namespace LogSetting {
    enum LogLevel{
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        NUM_LOG_LEVELS,
    };
    LogLevel G_LOG_LEVEL = TRACE;
    Ostream& G_LOG_STREAM = std::cout;
}

class LogStream : Noncopyable {
  public:
    LogStream(LogSetting::LogLevel level, Ostream& stream) : level_(level), stream_(stream) {}

    template<typename T>
    LogStream& operator<< (const T& t) {
        if(level_ >= LogSetting::G_LOG_LEVEL){
            stream_ << t; 
        }
        return *this;
    }

  private:
    const LogSetting::LogLevel level_;
    Ostream& stream_;
};

LogStream LOG_TRACE (LogSetting::TRACE, LogSetting::G_LOG_STREAM);
LogStream LOG_DEBUG (LogSetting::DEBUG, LogSetting::G_LOG_STREAM);
LogStream LOG_INFO (LogSetting::INFO, LogSetting::G_LOG_STREAM);
LogStream LOG_WARN (LogSetting::WARN, LogSetting::G_LOG_STREAM);
LogStream LOG_ERROR (LogSetting::ERROR, LogSetting::G_LOG_STREAM);
LogStream LOG_FATAL (LogSetting::FATAL, LogSetting::G_LOG_STREAM);


} // namespace LGG

#endif