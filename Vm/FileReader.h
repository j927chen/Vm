#ifndef FileReader_h
#define FileReader_h

#include <memory>
#include "Reader.h"

class Text;

class FileReader: public Reader {
    
public:
    std::unique_ptr<Text> read(const std::string &path) const override;
    bool isReadable(const std::string &path) const override;
};

#endif
