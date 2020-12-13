#ifndef VmCursor_h
#define VmCursor_h
#include "Cursor.h"
#include "Posn.h"

class Text;
class ConstTextIterator;

class VmCursor: public Cursor {
    
    const Text &text;
    std::unique_ptr<ConstTextIterator> it;
    Posn textPosn;
    Posn unboundedPosn;

    const Posn getInitialPosn();
    
public:
    VmCursor(const Text &text);
    VmCursor(const VmCursor &other);
    const Posn getPosn() const override;
    char get() const override;
    char next() const override;
    void setPosn(const Posn p) override;
    void moveLeftByOne() override;
    void moveRightByOne() override;
    void moveUpByOne() override;
    void moveDownByOne() override;
    std::unique_ptr<Cursor> clone() const override;
    ~VmCursor();
};

#endif
