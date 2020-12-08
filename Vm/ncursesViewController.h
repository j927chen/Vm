#ifndef ncursesViewController_h
#define ncursesViewController_h

#include <ncurses.h>
#include "TerminalViewController.h"

class Posn;


class ncursesViewController: public TerminalViewController {
    
public:
    ncursesViewController();
    
    const Posn getScrSize() const override;
    void print(char c, const Posn p) override;
    int get() override;
    
    ~ncursesViewController();
};

#endif
