#pragma once

namespace LGG
{
    
class Noncopyable {
  public:
    Noncopyable() = default;
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator= (const Noncopyable&) = delete;
};

}//end LGG

