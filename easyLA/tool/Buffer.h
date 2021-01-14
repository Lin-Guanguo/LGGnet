#pragma once
#include <sys/types.h>
#include <string_view>
#include "Noncopyable.h"

namespace LGG
{
    
class Buffer : Noncopyable {
protected:
    char* byteArray_;
    char* position_;
    char* limit_;
    char* capital_;

    char* mark_;
public:
    static Buffer allocate(size_t size){
        return {size};
    }

    Buffer(size_t size);

    ~Buffer();

    void resize(size_t size);

    /**
     * position置为0
     * 读模式下用于重读
     */
    void rewind() {
        position_ = byteArray_;
    }

    /**
     * position置为0，limit置为capital
     * 重置为初始状态，等待写
     */
    void clear() {
        position_ = byteArray_;
        limit_ = capital_;
    }

    /**
     * 将未读数据置放到开头
     * 保留未读数据，进入写模式
     */
    void compact();

    /**
     * 标记position
     */
    void mark() {
        mark_ = position_;
    }

    /**
     * position回到上一次标记位置
     * 未标记回到随机位置(warn)
     */
    void reset() {
        position_ = mark_;
    }

    /**
     * limit置为position，position置为0
     * 写模式转化为读模式
     */
    void flip() {
        limit_ = position_;
        position_ = byteArray_;
    }

    size_t remainingSize() {
        return limit_ - position_;
    }

    void put(std::string_view src);

    void put(const char* s, size_t len) {
        put({s, len});
    }

    size_t putFromFd(int fd);

    std::string_view get(size_t size) {
        auto p = position_;
        position_ += size;
        return {p, size};
    }

    std::string_view getAll() {
        auto p = position_;
        position_ = limit_;
        return {p, limit_ - p};
    }

    std::string_view seek(size_t size) {
        return {position_, size};
    }

    std::string_view seekAll() {
        return {position_, (limit_ - position_)};
    }

private:
    
};

} // namespace LGG
