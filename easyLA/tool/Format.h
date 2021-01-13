#ifndef LGGNET_TOOL_FORMATIO
#define LGGNET_TOOL_FORMATIO

#include "StaticClass.h"
#include <string>
#include <stdio.h>

namespace LGG
{

class Format : StaticClass{
  public:
    template<typename... T>
    static std::string concatToString(T... args){
        std::string s;
        constexpr int AVERAGE_ARG_LEN = 16;
        s.reserve(AVERAGE_ARG_LEN * sizeof...(args));
        (concat(args, s), ...);
        return std::move(s);
    }
    
    static void concat(int i, std::string& str) { str.append(std::to_string(i)); }
    static void concat(long i, std::string& str) { str.append(std::to_string(i)); }
    static void concat(long long i, std::string& str) { str.append(std::to_string(i)); }
    static void concat(unsigned int i, std::string& str) { str.append(std::to_string(i)); }
    static void concat(unsigned long i, std::string& str) { str.append(std::to_string(i)); }
    static void concat(unsigned long long i, std::string& str) { str.append(std::to_string(i)); }
    static void concat(double i, std::string& str) { str.append(std::to_string(i)); }
    static void concat(const char* cstr, std::string& str) { str.append(cstr); }
    static void concat(std::string_view cstr, std::string& str) { str.append(cstr); }
    static void concat(void* ptr, std::string& str) { str.append(std::to_string((long)ptr)); }

    template<typename... T>
    static void print(T... args){
        ::printf("%s", concatToString(std::forward<T>(args)...).data());
    }
  private:
};

} // namespace LGG

#endif
