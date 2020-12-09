#include "VmTextView.h"
#include "TerminalViewController.h"
#include "Text.h"
#include "Update.h"
#include "Posn.h"

VmTextView::VmTextView(TerminalViewController &terminalViewController): View{terminalViewController} {}

void VmTextView::accept(VmLoadFile &u) {
    display(u.text, *u.text.begin().get());
}

void VmTextView::accept(VmMoveCursorDown &u) {
    display(u.text, u.constTextIterator);
}

void VmTextView::accept(VmMoveCursorLeft &u) {
    display(u.text, u.constTextIterator);
}

void VmTextView::display(const Text &text, ConstTextIterator &constTextIterator) {
    Posn scrSize = terminalViewController.getScrSize();
    int x = 0;
    int y = 0;
    char c;
    for (auto it = constTextIterator.clone(); it->operator!=(*text.end().get()); it->operator++()) {
        
        if (y >= scrSize.y) return;
        
        c = it->operator*();
        
        if (x >= scrSize.x) {
            x = 0;
            ++y;
            if (c == '\n') continue;
        }
        
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

VmTextView::~VmTextView() {}

