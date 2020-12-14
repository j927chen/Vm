#include <string>
#include "VmStatusBarView.h"
#include "TerminalViewController.h"
#include "Cursor.h"
#include "Update.h"

VmStatusBarView::VmStatusBarView(TerminalViewController &terminalViewController): View{terminalViewController}, terminalXCursorPosn{terminalViewController.getScrWidth() - 15}, terminalXMultiplierPosn{terminalXCursorPosn - 10}, terminalYTop{terminalViewController.getScrHeight() - 1} {}

void VmStatusBarView::displayCursorPosn(const Posn &cursorPosn) {
    int x = terminalXCursorPosn;
    const std::string cursorRowNum = std::to_string(cursorPosn.y);
    for (auto it = cursorRowNum.begin(); it != cursorRowNum.end(); ++it) {
        terminalViewController.print(*it, Posn {x++, terminalYTop});
    }
    terminalViewController.print(',', Posn {x++, terminalYTop});
    const std::string colNum = std::to_string(cursorPosn.x);
    for (auto it = colNum.begin(); it != colNum.end(); ++it) {
        terminalViewController.print(*it, Posn {x++, terminalYTop});
    }
    terminalViewController.clearToEOL(Posn {x, terminalYTop});
}

void VmStatusBarView::displayCursorPosn(const Posn &cursorPosn, const std::string &colReplacement) {
    int x = terminalXCursorPosn;
    const std::string cursorRowNum = std::to_string(cursorPosn.y);
    for (auto it = cursorRowNum.begin(); it != cursorRowNum.end(); ++it) {
        terminalViewController.print(*it, Posn {x++, terminalYTop});
    }
    terminalViewController.print(',', Posn {x++, terminalYTop});
    for (auto it = colReplacement.begin(); it != colReplacement.end(); ++it) {
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
    if (u.cursor.getPosn().x == 0 || u.cursor.get() == '\n') {
        displayCursorPosn(u.cursor.getPosn(), standardZeroCursorColReplacement);
    } else displayCursorPosn(u.cursor.getPosn());
}

void VmStatusBarView::accept(const VmCommandMode &u) {
    terminalViewController.clearToEOL(Posn {0, terminalYTop});
    int x = 0;
    for (auto it = u.message.begin(); it != u.message.end(); ++it) {
        terminalViewController.print(*it, Posn {x++, terminalYTop});
    }
    if (u.cursor.getPosn().x == 0 || u.cursor.get() == '\n') {
        displayCursorPosn(u.cursor.getPosn(), standardZeroCursorColReplacement);
    } else displayCursorPosn(u.cursor.getPosn());
}

void VmStatusBarView::accept(const VmCommandEnterMode &u) {
    int x = 0;
    for (auto it = u.typedCommand.begin(); it != u.typedCommand.end(); ++it) {
        terminalViewController.print(*it, Posn {x++, terminalYTop});
    }
    terminalViewController.finalCursorPosn = Posn {x, terminalYTop};
    terminalViewController.clearToEOL(Posn {x, terminalYTop});
}

void VmStatusBarView::accept(const VmInsertMode &u) {
    int x = 0;
    const std::string mode = "-- INSERT --";
    for (auto it = mode.begin(); it != mode.end(); ++it) {
        terminalViewController.print(*it, Posn {x++, terminalYTop});
    }
    terminalViewController.clearToEOL(Posn {x, terminalYTop});
    if (u.cursor.getPosn().x == 0) displayCursorPosn(u.cursor.getPosn(), "1");
    else displayCursorPosn(u.cursor.getPosn());
}

void VmStatusBarView::accept(const VmMultiplier &u) {
    if (u.multiplier == 0) clearMultiplier();
    else {
        const std::string multiplier = std::to_string(u.multiplier);
        int x = terminalXMultiplierPosn;
        for (auto it = multiplier.begin(); it != multiplier.end(); ++it) {
            terminalViewController.print(*it, Posn {x++, terminalYTop});
        }
    }
}

void VmStatusBarView::accept(const VmMoveCursor &u) {
    if (u.cursor.getPosn().x == 0 || u.cursor.get() == '\n') {
        displayCursorPosn(u.cursor.getPosn(), standardZeroCursorColReplacement);
    } else displayCursorPosn(u.cursor.getPosn());
    clearMultiplier();
}

void VmStatusBarView::accept(const VmMoveCursorUp &u) {
    accept(static_cast<const VmMoveCursor&>(u));
}
void VmStatusBarView::accept(const VmMoveCursorDown &u) {
    accept(static_cast<const VmMoveCursor&>(u));
}
void VmStatusBarView::accept(const VmMoveCursorLeft &u) {
    accept(static_cast<const VmMoveCursor&>(u));
}
void VmStatusBarView::accept(const VmMoveCursorRight &u) {
    accept(static_cast<const VmMoveCursor&>(u));
}

void VmStatusBarView::clearMultiplier() {
    for (int x = terminalXMultiplierPosn; x < terminalXCursorPosn; ++x) {
        terminalViewController.print(' ', Posn {x, terminalYTop});
    }
}

VmStatusBarView::~VmStatusBarView() {}
