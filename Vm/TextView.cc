#include "TextView.h"
#include "TerminalViewController.h"
#include "Text.h"
#include "Posn.h"

void TextView::display(const Text &text, ConstTextIterator &constTextIterator) {
    Posn scrSize = terminalViewController.getScrSize();
    int x = 0;
    int y = 0;
    char c;
    for (auto it = constTextIterator.clone(); it->operator!=(*text.end().get()); it->operator++()) {
        
        if (x >= scrSize.x) {
            x = 0;
            ++y;
        }
        
        if (y >= scrSize.y) return;
        
        c = it->operator*();
        terminalViewController.print(c, Posn(x, y));
        
        if (c == '\n') {
            x = 0;
            ++y;
        } else ++x;
    }
    
    for (; y < scrSize.y; ++y) {
        terminalViewController.print('~', Posn(0, y));
    }
}

TextView::~TextView() {}
