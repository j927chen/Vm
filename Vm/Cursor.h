#ifndef Cursor_h
#define Cursor_h

class Posn;

class Cursor {
    
public:
    virtual const Posn getPosn() const = 0;
    virtual void setPosn(const Posn p) = 0;
    virtual void moveLeftByOne() = 0;
    virtual void moveRightByOne() = 0;
    virtual void moveUpByOne() = 0;
    virtual void moveDownByOne() = 0;
    virtual ~Cursor();
};

#endif
