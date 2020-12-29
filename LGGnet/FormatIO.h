#ifndef LGGNET_FORMATIO
#define LGGNET_FORMATIO

#include <string>

namespace LGG
{

class FormatIO{
  public:
    FormatIO() = delete;
    template<typename... T>
    static std::string toString(T... args){
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
