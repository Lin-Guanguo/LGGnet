#ifndef LGGNET_FORMATIO
#define LGGNET_FORMATIO

#include "StaticClass.h"
#include <string>

namespace LGG
{

class Format : StaticClass{
  public:
    Format() = delete;
    template<typename... T>
    static std::string format(T... args){
        std::string s;
        (formatData(args, s), ...);
        return std::move(s);
    }
    
    static void formatData(int i, std::string& str) { str.append(std::to_string(i)); }
    static void formatData(double i, std::string& str) { str.append(std::to_string(i)); }
    static void formatData(const char* cstr, std::string& str) { str.append(cstr); }
  private:
};

} // namespace LGG

#endif
