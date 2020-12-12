#ifndef TerminalViewController_h
#define TerminalViewController_h

#include "Posn.h"

class TerminalViewController {
    
public:
    Posn finalCursorPosn;
    TerminalViewController();
    virtual void moveCursorToFinalPosn() = 0;
    virtual const Posn getScrSize() const = 0;
    virtual const int getScrWidth() const = 0;
    virtual const int getScrHeight() const = 0;
    virtual void print(char c, const Posn p) = 0;
    virtual void clearToEOL(const Posn p) = 0;
    virtual int get() = 0;
    virtual int getBackspaceCode() const = 0;
    virtual ~TerminalViewController();
};

#endif
