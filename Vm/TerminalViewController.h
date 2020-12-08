#ifndef TerminalViewController_h
#define TerminalViewController_h

class Posn;

class TerminalViewController {

public:
    virtual const Posn getScrSize() const = 0;
    virtual void print(char c, const Posn p) = 0;
    virtual int get() = 0;
    virtual ~TerminalViewController();
};

#endif
