#include "Format.h"
#include <memory>

using namespace LGG;

template<typename... T>
void Format::print(T... args){
    ::printf("%s", concatToString(std::forward<T>(args)...).data());
}