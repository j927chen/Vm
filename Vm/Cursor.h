#ifndef Cursor_h
#define Cursor_h

#include <memory>

class Posn;
class ConstTextIterator;
class Text;

class Cursor {
    
public:
    virtual const Posn getPosn() const = 0;
    virtual const ConstTextIterator &getIt() const = 0;
    virtual const Text &getText() const = 0;
    virtual char get() const = 0;
    virtual char getNext() const = 0;
    virtual void setPosn(const Posn p) = 0;
    virtual void resetUnboundedPosn() = 0;
    virtual void moveLeftByOne() = 0;
    virtual void moveRightByOne() = 0;
    virtual void moveRightByOneNoNewLine() = 0;
    virtual void moveUpByOne() = 0;
    virtual void moveUpByOneNoNewLine() = 0;
    virtual void moveDownByOne() = 0;
    virtual void moveDownByOneNoNewLine() = 0;
    virtual std::unique_ptr<Cursor> clone() const = 0;
    virtual std::unique_ptr<Cursor> clonePrevious() const = 0;
    virtual ~Cursor();
};

#endif
