#ifndef Reader_h
#define Reader_h

#include <memory>

class Text;

class Reader {
    
public:
    virtual std::unique_ptr<Text> read(const std::string &path) const = 0;
    virtual bool isReadable(const std::string &path) const = 0;
    virtual ~Reader();
};

#endif
