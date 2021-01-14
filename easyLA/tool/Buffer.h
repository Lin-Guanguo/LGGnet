#pragma once

#include <string_view>
#include <cassert>
#include "Noncopyable.h"

namespace LGG
{
    
class Buffer : Noncopyable {
    char* byteArray_;
    char* position_;
    char* limit_;
    char* capital_;

    char* mark_;
    bool mode_ = WRITE;
public:
    static Buffer allocate(size_t size){
        return {size};
    }

    Buffer(size_t size);

    ~Buffer();

    enum Mode : short {
        READ = 0, WRITE = 1
    };

    void writeMode() {
        if(mode_ != WRITE){
            compact();
        }
    }

    void readMode() {
        if(mode_ != READ){
            flip();
        }
    }

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
        mode_ = WRITE;
        position_ = byteArray_;
        limit_ = capital_;
    }

    /**
     * 将未读数据置放到开头
     * 保留未读数据，进入写模式
     */
    void compact();

    /**
     * limit置为position，position置为0
     * 写模式转化为读模式
     */
    void flip() {
        mode_ = READ;
        limit_ = position_;
        position_ = byteArray_;
    }

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

    size_t remainingSize() {
        assert(limit_ >= position_);
        return static_cast<size_t>(limit_ - position_);
    }

    void put(std::string_view src);

    void put(const char* s, size_t len) {
        put({s, len});
    }

    size_t putFromFd(int fd);

    std::string_view get(size_t size) {
        assert(mode_ == READ);
        auto p = position_;
        position_ += size;
        return {p, size};
    }

    std::string_view getAll() {
        assert(mode_ == READ);
        assert(limit_ >= position_);
        auto p = position_;
        position_ = limit_;
        return {p, static_cast<size_t>(limit_ - p)};
    }

    std::string_view getLine();

    std::string_view seek(size_t size) {
        assert(mode_ == READ);
        return {position_, size};
    }

    std::string_view seekAll() {
        assert(mode_ == READ);
        assert(limit_ >= position_);
        return {position_, static_cast<size_t>(limit_ - position_)};
    }

private:
    
};

} // namespace LGG
