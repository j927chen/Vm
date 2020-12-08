#ifndef FileWriter_h
#define FileWriter_h

#include "Writer.h"

class FileWriter: public Writer {
    
public:
    void write(const std::string &path, const Text &text) const override;
    bool isWritable(const std::string &path) const override;
    ~FileWriter();
};

#endif 
