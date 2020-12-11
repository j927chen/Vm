#include <string>
#include "VmStatusBarView.h"
#include "TerminalViewController.h"
#include "Update.h"

VmStatusBarView::VmStatusBarView(TerminalViewController &terminalViewController): View{terminalViewController} {}

void VmStatusBarView::displayCursorPosn(const Posn cursorPosn) {
    int x = terminalViewController.getScrWidth() - 11;
    int y = terminalViewController.getScrHeight() - 1;
    const std::string cursorRowNum = std::to_string(cursorPosn.y);
    for (auto it = cursorRowNum.begin(); it != cursorRowNum.end(); ++it) {
        terminalViewController.print(*it, Posn {x++, y});
    }
    terminalViewController.print(',', Posn {x++, y});
    const std::string cursorColNum = std::to_string(cursorPosn.x);
    for (auto it = cursorColNum.begin(); it != cursorColNum.end(); ++it) {
        terminalViewController.print(*it, Posn {x++, y});
    }
    terminalViewController.clearToEOL(Posn {x, y});
}

void VmStatusBarView::accept(const VmLoadFile &u) {
    int x = 0;
    int y = terminalViewController.getScrHeight() - 1;
    terminalViewController.print('"', Posn {x++, y});
    for (auto it = u.fileName.begin(); it != u.fileName.end(); ++it) {
        terminalViewController.print(*it, Posn {x++, y});
    }
    terminalViewController.print('"', Posn {x++, y});
    displayCursorPosn(u.cursorPosn);
}

void VmStatusBarView::accept(const VmMoveCursorUp &u) {
    displayCursorPosn(u.cursorPosn);
}
void VmStatusBarView::accept(const VmMoveCursorDown &u) {
    displayCursorPosn(u.cursorPosn);
}
void VmStatusBarView::accept(const VmMoveCursorLeft &u) {
    displayCursorPosn(u.cursorPosn);
}
void VmStatusBarView::accept(const VmMoveCursorRight &u) {
    displayCursorPosn(u.cursorPosn);
}

VmStatusBarView::~VmStatusBarView() {}
