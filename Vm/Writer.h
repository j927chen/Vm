#ifndef Writer_h
#define Writer_h

#include <string>

class Text;

class Writer {
    
public:
    virtual void write(const std::string &path, const Text &text) const = 0;
    virtual bool isWritable(const std::string &path) const = 0;
    virtual ~Writer();
    
    class invalidPath{};
};

#endif
