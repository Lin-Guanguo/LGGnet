#ifndef LGGNET_TOOL_BUFFER
#define LGGNET_TOOL_BUFFER

#include <sys/types.h>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include "Log.h"

namespace LGG
{

class Buffer {
    static constexpr size_t INI_SIZE = 1024;
    static constexpr size_t INI_PRE_SIZE = 8;

    char* begin_;
    size_t read_;
    size_t write_;
    size_t limit_;
  public:
    Buffer() 
      : read_(INI_PRE_SIZE), 
        write_(INI_PRE_SIZE),
        limit_(INI_PRE_SIZE + INI_SIZE) 
    {
        begin_ = (char*)::malloc(sizeof(char) * (INI_PRE_SIZE + INI_SIZE) );
        if(!begin_){
            LOG_FATAL("out of memory");
            abort();
        }
    };

    ~Buffer() {
        ::free(begin_);
    };

    void write(const char* src, size_t len){
        if(limit_ - write_ < len){
            reserve(len);
        }
        ::memcpy(begin_ + write_, src, len);
        write_ += len;
    }

    void read(char* dest, size_t len){
        assert(len <= write_ - read_);
        ::memcpy(dest, begin_ + read_ , len);
        read_ += len;
    }
    
    void preAppend(const char* src, size_t len) {
        if(read_ >= len);
    }

    
  private:
    void reserve(size_t moreSpace){
        assert(limit_ - write_ < moreSpace);
        auto restSize = read_ + limit_ - write_ - INI_PRE_SIZE;
        if( restSize >= moreSpace){
            moveMem();
        }else{
            expandMem(write_ - read_ + moreSpace);
        }
    }

    void expandMem(size_t newLen){
        LOG_TRACE("Buffer expand ", newLen);

        auto len = INI_SIZE;
        while(len <= newLen) len *= 2;
        begin_ = (char*)::realloc(begin_, sizeof(char) * (INI_PRE_SIZE + len));
        if(!begin_){
            LOG_FATAL("out of memory");
            abort();
        }
        limit_ = len + INI_PRE_SIZE;
    }

    void moveMem(){
        LOG_TRACE("Buffer moveMem");
        ::memcpy(begin_ + INI_PRE_SIZE, begin_ + read_, write_ - read_);
        write_ = write_ - read_ + INI_PRE_SIZE;
        read_ = INI_PRE_SIZE;
    }
};

} // namespace LGG

#endif