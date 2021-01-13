#pragma once

#include <cassert>
#include <deque>
#include "Log.h"
#include "Noncopyable.h"

namespace LGG
{

class Buffer : Noncopyable {
    static constexpr size_t INI_SIZE = 1024;
    using size_type = std::deque<char>::size_type;

    std::deque<char> buf_;
public:
    Buffer() : buf_() {}

    std::string read(size_type len) {
        assert(len <= readableSize());
        std::string res;
        res.reserve(len);
        std::move(buf_.begin(), buf_.begin() + len, std::back_insert_iterator(res));
        buf_.erase(buf_.begin(), buf_.begin() + len);
        return res;
    }

    std::string readAll() {
        return this->read(buf_.size());
    }

    std::string readLine() {
        auto lineEnd = std::find(buf_.begin(), buf_.end(), '\n');
        if(lineEnd == buf_.end()){
            LOG_TRACE("read line faied, {}");
            return {};
        }else{
            std::string res;
            res.reserve(lineEnd - buf_.begin());
            std::move(buf_.begin(), lineEnd + 1, std::back_insert_iterator(res));
            buf_.erase(buf_.begin(), lineEnd + 1);
            LOG_TRACE("read line: ", res);
            return res;
        }
    }

    std::string seek(size_type len) const {
        assert(len <= readableSize());
        std::string res;
        res.reserve(len);
        std::move(buf_.begin(), buf_.begin() + len, std::back_insert_iterator(res));
        return res;
    }

    void writePre(std::string_view str) {
        std::copy(str.rbegin(), str.rend(), std::front_insert_iterator(buf_));
    }

    void write(std::string_view str) {
        std::copy(str.begin(), str.end(), std::back_insert_iterator(buf_));
    }

    ssize_t writeFromFd(int fd);

    size_type readableSize() const { return buf_.size(); }

    
};

} // namespace LGG
