#include <string>
#include "VmStatusBarView.h"
#include "TerminalViewController.h"
#include "Update.h"

VmStatusBarView::VmStatusBarView(TerminalViewController &terminalViewController): View{terminalViewController}, terminalXCursorPosn{terminalViewController.getScrWidth() - 11}, terminalYTop{terminalViewController.getScrHeight() - 1} {}

void VmStatusBarView::displayCursorPosn(const Posn cursorPosn) {
    int x = terminalXCursorPosn;
    const std::string cursorRowNum = std::to_string(cursorPosn.y);
    for (auto it = cursorRowNum.begin(); it != cursorRowNum.end(); ++it) {
        terminalViewController.print(*it, Posn {x++, terminalYTop});
    }
    terminalViewController.print(',', Posn {x++, terminalYTop});
    const std::string cursorColNum = cursorPosn.x ? std::to_string(cursorPosn.x) : "0-1";
    for (auto it = cursorColNum.begin(); it != cursorColNum.end(); ++it) {
        terminalViewController.print(*it, Posn {x++, terminalYTop});
    }
    terminalViewController.clearToEOL(Posn {x, terminalYTop});
}

void VmStatusBarView::accept(const NoUpdate &u) {}

void VmStatusBarView::accept(const VmLoadFile &u) {
    if (!u.fileName.empty()) {
        int x = 0;
        terminalViewController.print('"', Posn {x++, terminalYTop});
        for (auto it = u.fileName.begin(); it != u.fileName.end(); ++it) {
            terminalViewController.print(*it, Posn {x++, terminalYTop});
        }
        terminalViewController.print('"', Posn {x++, terminalYTop});
    }
    displayCursorPosn(u.cursorPosn);
}

void VmStatusBarView::accept(const VmCommandMode &u) {
    terminalViewController.clearToEOL(Posn {0, terminalYTop});
    displayCursorPosn(u.cursorPosn);
}

void VmStatusBarView::accept(const VmCommandEnterMode &u) {
    int x = 0;
    for (auto it = u.typedCommand.begin(); it != u.typedCommand.end(); ++it) {
        terminalViewController.print(*it, Posn {x++, terminalYTop});
    }
    terminalViewController.finalCursorPosn = Posn {x, terminalYTop};
    terminalViewController.clearToEOL(Posn {x, terminalYTop});
}

void VmStatusBarView::accept(const VmMoveCursor &u) {
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
