#ifndef Cursor_h
#define Cursor_h

#include <memory>

class Posn;

class Cursor {
    
public:
    virtual const Posn getPosn() const = 0;
    virtual char get() const = 0;
    virtual char next() const = 0;
    virtual void setPosn(const Posn p) = 0;
    virtual void moveLeftByOne() = 0;
    virtual void moveRightByOne() = 0;
    virtual void moveUpByOne() = 0;
    virtual void moveDownByOne() = 0;
    virtual std::unique_ptr<Cursor> clone() const = 0;
    virtual ~Cursor();
};

#endif
