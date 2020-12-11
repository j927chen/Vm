#include "VmTextView.h"
#include "TerminalViewController.h"
#include "Text.h"
#include "Update.h"
#include "Posn.h"

VmTextView::VmTextView(TerminalViewController &terminalViewController): View{terminalViewController}, firstDisplayedTextRowNum{1}, maxHeight{terminalViewController.getScrHeight() - 1} {}

const Posn VmTextView::convertTextPosnToTerminalPosn(const Posn p) {
    return Posn{p.x ? p.x - 1 : 0, p.y ? p.y - 1 : 0};
}

void VmTextView::accept(const VmLoadFile &u) {
    display(*u.text.begin().get(), *u.text.end().get());
}

void VmTextView::accept(const VmMoveCursorDown &u) {
 
}

void VmTextView::accept(const VmMoveCursorLeft &u) {
    Posn cursorPosn = u.cursorPosn;
    int scrWidth = terminalViewController.getScrWidth();
    int relativeTextRow = (cursorPosn.x - 1) / scrWidth + cursorPosn.y - firstDisplayedTextRowNum + 1;
    int relativeTextColumn = cursorPosn.x ? cursorPosn.x % scrWidth ? cursorPosn.x % scrWidth : scrWidth : 0;
    terminalViewController.finalCursorPosn = convertTextPosnToTerminalPosn(Posn {relativeTextColumn, relativeTextRow});
}

void VmTextView::accept(const VmMoveCursorRight &u) {
    accept(VmMoveCursorLeft {u.text, u.cursorPosn});
}


void VmTextView::display(ConstTextIterator &begin, ConstTextIterator &end) {
    Posn scrSize = terminalViewController.getScrSize();
    int x = 0;
    int y = 0;
    char c;
    for (auto it = begin.clone(); it->operator!=(end); it->operator++()) {
        
        if (y >= maxHeight) return;
        
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
    
    for (; y < maxHeight; ++y) {
        if (y) terminalViewController.print('~', Posn(0, y));
    }
}

VmTextView::~VmTextView() {}

