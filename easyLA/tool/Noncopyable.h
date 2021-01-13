#ifndef LGGNET_TOOL_NONCOPYABLE
#define LGGNET_TOOL_NONCOPYABLE

namespace LGG
{
    
class Noncopyable {
  public:
    Noncopyable() = default;
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator= (const Noncopyable&) = delete;
};

}//end LGG

#endif
