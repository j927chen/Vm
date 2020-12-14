#ifndef Editable_h
#define Editable_h

#include <memory>

class Cursor;

class Editable {
    
public:
    virtual std::unique_ptr<Cursor> insertCharAt(char c, const Cursor &cursor) = 0;
    virtual std::unique_ptr<Cursor> removeCharAt(const Cursor &cursor) = 0;
    virtual ~Editable();
};

#endif
