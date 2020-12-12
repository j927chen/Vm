#ifndef Editable_h
#define Editable_h

#include <memory>

class Cursor;

class Editable {
    
public:
    virtual std::unique_ptr<Cursor> insertCharAt(char c, Cursor &cursor) = 0;
    virtual std::unique_ptr<Cursor> removeCharAt(char c, Cursor &cursor) = 0;
    virtual ~Editable();
};

#endif
