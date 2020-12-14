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
    VmCursor(const Text &text, const ConstTextIterator &it);
    
    const Posn getPosn() const override;
    const ConstTextIterator &getIt() const override;
    const Text &getText() const override;
    char get() const override;
    char getNext() const override;
    void setPosn(const Posn p) override;
    void resetUnboundedPosn() override;
    void moveLeftByOne() override;
    void moveRightByOne() override;
    void moveRightByOneNoNewLine() override;
    void moveUpByOne() override;
    void moveUpByOneNoNewLine() override;
    void moveDownByOne() override;
    void moveDownByOneNoNewLine() override;
    std::unique_ptr<Cursor> clone() const override;
    std::unique_ptr<Cursor> clonePrevious() const override;
    ~VmCursor();
};

#endif
