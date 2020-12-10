#ifndef ncursesViewController_h
#define ncursesViewController_h

#include "TerminalViewController.h"

class ncursesViewController: public TerminalViewController {
    
public:
    ncursesViewController() ;
    void moveCursorToFinalPosn() override;
    const Posn getScrSize() const override;
    void print(char c, const Posn p) override;
    int get() override;
    
    ~ncursesViewController();
};

#endif
