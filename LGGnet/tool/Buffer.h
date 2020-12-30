#ifndef LGGNET_TOOL_BUFFER
#define LGGNET_TOOL_BUFFER

#include <cassert>
#include <deque>
#include "Log.h"

namespace LGG
{

class Buffer {
    static constexpr size_t INI_SIZE = 1024;
    using size_type = std::deque<char>::size_type;

    std::deque<char> buf_;
  public:
    Buffer() : buf_() {}

    std::string read(size_type len) {
        std::string res;
        res.reserve(len);
        std::move(buf_.begin(), buf_.begin() + len, std::back_insert_iterator(res));
        buf_.erase(buf_.begin(), buf_.begin() + len);
        return res;
    }

    std::string readAll() {
        return this->read(buf_.size());
    }

    std::string seek(size_type len) {
        std::string res;
        res.reserve(len);
        std::move(buf_.begin(), buf_.begin() + len, std::back_insert_iterator(res));
        return res;
    }

    void write(std::string_view str) {
        std::copy(str.begin(), str.end(), std::back_insert_iterator(buf_));
    }
};

} // namespace LGG

#endif