#ifndef ncursesViewController_h
#define ncursesViewController_h

#include "TerminalViewController.h"

class ncursesViewController: public TerminalViewController {
    
public:
    ncursesViewController() ;
    void moveCursorToFinalPosn() override;
    const Posn getScrSize() const override;
    const int getScrWidth() const override;
    const int getScrHeight() const override;
    void print(char c, const Posn p) override;
    int get() override;
    
    ~ncursesViewController();
};

#endif
