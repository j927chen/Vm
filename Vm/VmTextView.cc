#include "VmTextView.h"
#include "TerminalViewController.h"
#include "Text.h"
#include "Update.h"
#include "Posn.h"

VmTextView::VmTextView(TerminalViewController &terminalViewController): View{terminalViewController}, firstDisplayedRow{1} {}

const Posn VmTextView::convertTextPosnToTerminalPosn(const Posn &p) {
    return Posn{p.x - 1, p.y - 1};
}

void VmTextView::accept(const VmLoadFile &u) {
    display(*u.text.begin().get(), *u.text.end().get());
    terminalViewController.moveCursorToFinalPosn();
}

void VmTextView::accept(const VmMoveCursorDown &u) {
 
}

void VmTextView::accept(const VmMoveCursorLeft &u) {
    int relativeTextRow = (u.cursorPosn.y ? u.cursorPosn.y : 1) - firstDisplayedRow + 1;
    terminalViewController.finalCursorPosn = convertTextPosnToTerminalPosn(Posn {u.cursorPosn.x ? u.cursorPosn.x : 1, relativeTextRow});
    terminalViewController.moveCursorToFinalPosn();
}

void VmTextView::accept(const VmMoveCursorRight &u) {
    int relativeTextRow = (u.cursorPosn.y ? u.cursorPosn.y : 1) - firstDisplayedRow + 1;
    terminalViewController.finalCursorPosn = convertTextPosnToTerminalPosn(Posn {u.cursorPosn.x ? u.cursorPosn.x : 1, relativeTextRow});
    terminalViewController.moveCursorToFinalPosn();
}


void VmTextView::display(ConstTextIterator &begin, ConstTextIterator &end) {
    Posn scrSize = terminalViewController.getScrSize();
    int x = 0;
    int y = 0;
    char c;
    for (auto it = begin.clone(); it->operator!=(end); it->operator++()) {
        
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

