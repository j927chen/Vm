#include "VmTextView.h"
#include "TerminalViewController.h"
#include "Text.h"
#include "Cursor.h"
#include "Update.h"
#include "Posn.h"

VmTextView::VmTextView(TerminalViewController &terminalViewController): View{terminalViewController}, firstDisplayedTextRowNum{1}, maxWidth{terminalViewController.getScrWidth()}, maxHeight{terminalViewController.getScrHeight() - 1} {}

void VmTextView::accept(const NoUpdate &u) {}

void VmTextView::accept(const VmLoadFile &u) {
    auto it = u.text.beginAtLine(firstDisplayedTextRowNum);
    display(*it, *u.text.end());
    moveCursor(u.cursor.getPosn().x, getMinRelativeTextViewRowNum(u.cursor.getPosn().y, *it));
}

void VmTextView::accept(const VmCommandMode &u) {
    accept(static_cast<const VmMoveCursor>(u));
}

void VmTextView::accept(const VmCommandEnterMode &u) {}

void VmTextView::accept(const VmInsertMode &u) {
    const Text &text = u.cursor.getText();
    const Posn cursorPosn = u.cursor.getPosn();
    auto itAtFirstDisplayedTextRow = text.beginAtLine(firstDisplayedTextRowNum);
    int currentRelativeTextViewRowNum = getMinRelativeTextViewRowNum(cursorPosn.y, *itAtFirstDisplayedTextRow);
    
    if (firstDisplayedTextRowNum > 1 && currentRelativeTextViewRowNum <= 5) {
        --firstDisplayedTextRowNum;
        text.goBackToStartOfPreviousLine(*itAtFirstDisplayedTextRow);
        currentRelativeTextViewRowNum = getMinRelativeTextViewRowNum(cursorPosn.y, *itAtFirstDisplayedTextRow);
    } else  {
        int currentMaxRelativeTextViewRowNum = getMaxRelativeTextViewRowNum(cursorPosn.y, *itAtFirstDisplayedTextRow);
        int endOfDisplay = checkEndOfDisplay(*itAtFirstDisplayedTextRow, *text.end());
        if (endOfDisplay != 0 && currentMaxRelativeTextViewRowNum >= maxHeight - 4) {
            do {
                ++firstDisplayedTextRowNum;
                text.advanceToStartOfNextLine(*itAtFirstDisplayedTextRow);
                currentRelativeTextViewRowNum = getMinRelativeTextViewRowNum(cursorPosn.y, *itAtFirstDisplayedTextRow);
                currentMaxRelativeTextViewRowNum = getMaxRelativeTextViewRowNum(cursorPosn.y, *itAtFirstDisplayedTextRow);
                endOfDisplay = checkEndOfDisplay(*itAtFirstDisplayedTextRow, *text.end());
            } while (endOfDisplay == -1);
        }
    }
    display(*itAtFirstDisplayedTextRow, *text.end());
    moveCursor(cursorPosn.x, currentRelativeTextViewRowNum);
}

void VmTextView::accept(const VmMultiplier &u) {}



void VmTextView::accept(const VmMoveCursor &u) {
    int previousFirstDisplayedTextRowNum = firstDisplayedTextRowNum;
    const Text &text = u.cursor.getText();
    const Posn cursorPosn = u.cursor.getPosn();
    auto itAtFirstDisplayedTextRow = text.beginAtLine(firstDisplayedTextRowNum);
    int currentTextRowNum = u.previousCursorPosn.y;
    int currentRelativeTextViewRowNum = getMinRelativeTextViewRowNum(u.previousCursorPosn.y, *itAtFirstDisplayedTextRow);
    while (currentTextRowNum != cursorPosn.y) {
        if (currentTextRowNum < cursorPosn.y) {
            ++currentTextRowNum;
            currentRelativeTextViewRowNum = getMinRelativeTextViewRowNum(currentTextRowNum, *itAtFirstDisplayedTextRow);
            int currentMaxRelativeTextViewRowNum = getMaxRelativeTextViewRowNum(currentTextRowNum, *itAtFirstDisplayedTextRow);
            int endOfDisplay = checkEndOfDisplay(*itAtFirstDisplayedTextRow, *text.end());
            if (endOfDisplay == 0) continue;
            if (currentMaxRelativeTextViewRowNum >= maxHeight - 4) {
                do {
                    ++firstDisplayedTextRowNum;
                    text.advanceToStartOfNextLine(*itAtFirstDisplayedTextRow);
                    currentRelativeTextViewRowNum = getMinRelativeTextViewRowNum(currentTextRowNum, *itAtFirstDisplayedTextRow);
                    currentMaxRelativeTextViewRowNum = getMaxRelativeTextViewRowNum(currentTextRowNum, *itAtFirstDisplayedTextRow);
                    endOfDisplay = checkEndOfDisplay(*itAtFirstDisplayedTextRow, *text.end());
                } while (endOfDisplay == -1);
            }
        } else {
            --currentTextRowNum;
            currentRelativeTextViewRowNum = getMinRelativeTextViewRowNum(currentTextRowNum, *itAtFirstDisplayedTextRow);
            if (firstDisplayedTextRowNum == 1) continue;
            if (currentRelativeTextViewRowNum <= 5) {
                --firstDisplayedTextRowNum;
                text.goBackToStartOfPreviousLine(*itAtFirstDisplayedTextRow);
                currentRelativeTextViewRowNum = getMinRelativeTextViewRowNum(currentTextRowNum, *itAtFirstDisplayedTextRow);
            }
        }
    }
    if (previousFirstDisplayedTextRowNum != firstDisplayedTextRowNum) {
        display(*itAtFirstDisplayedTextRow, *text.end());
    }
    moveCursor(cursorPosn.x, currentRelativeTextViewRowNum);
}

void VmTextView::accept(const VmMoveCursorUp &u) {
    accept(static_cast<const VmMoveCursor>(u));
}

void VmTextView::accept(const VmMoveCursorDown &u) {
    accept(static_cast<const VmMoveCursor>(u));
}

void VmTextView::accept(const VmMoveCursorLeft &u) {
    accept(static_cast<const VmMoveCursor>(u));
}

void VmTextView::accept(const VmMoveCursorRight &u) {
    accept(static_cast<const VmMoveCursor>(u));
}

const Posn VmTextView::convertTextPosnToTerminalPosn(const Posn p) {
    return Posn{p.x ? p.x - 1 : 0, p.y ? p.y - 1 : 0};
}

int VmTextView::getMinRelativeTextViewRowNum(int textLineNum, const ConstTextIterator &itAtBeginningOfFirstDisplayedTextRow) const {
    int currTextLineNum = firstDisplayedTextRowNum;
    int textViewRowNum = 1;
    int textViewColumnNum = 1;
    for (auto it = itAtBeginningOfFirstDisplayedTextRow.clone(); currTextLineNum < textLineNum; it->operator++()) {
        if (textViewColumnNum > terminalViewController.getScrWidth()) {
            textViewColumnNum = 1;
            ++textViewRowNum;
            if (it->operator*() == '\n') ++currTextLineNum;
            continue;
        }
        if (it->operator*() == '\n') {
            textViewColumnNum = 1;
            ++textViewRowNum;
            ++currTextLineNum;
        } else ++textViewColumnNum;
    }
    return textViewRowNum;
}

int VmTextView::getMaxRelativeTextViewRowNum(int textLineNum, const ConstTextIterator &itAtBeginningOfFirstDisplayedTextRow) const {
    int currTextLineNum = firstDisplayedTextRowNum;
    int textViewRowNum = 1;
    int textViewColumnNum = 1;
    for (auto it = itAtBeginningOfFirstDisplayedTextRow.clone(); currTextLineNum <= textLineNum; it->operator++()) {
        if (textViewColumnNum > terminalViewController.getScrWidth()) {
            textViewColumnNum = 1;
            ++textViewRowNum;
            if (it->operator*() == '\n') ++currTextLineNum;
            continue;
        }
        if (it->operator*() == '\n') {
            textViewColumnNum = 1;
            ++textViewRowNum;
            ++currTextLineNum;
        } else ++textViewColumnNum;
    }
    return textViewRowNum - 1;
}

void VmTextView::moveCursor(int textColumnNum, int relativeTextViewRowNum) {
    int scrWidth = terminalViewController.getScrWidth();
    int relativeTextRow = (textColumnNum - 1) / scrWidth + relativeTextViewRowNum;
    int relativeTextColumn = textColumnNum ? textColumnNum % scrWidth ? textColumnNum % scrWidth : scrWidth : 0;
    terminalViewController.finalCursorPosn = convertTextPosnToTerminalPosn(Posn {relativeTextColumn, relativeTextRow});
}

void VmTextView::display(ConstTextIterator &begin, ConstTextIterator &end) {
    int textViewRowNum = 1;
    int textViewColumnNum = 1;
    char c;
    auto it = begin.clone();
    for (; it->operator!=(end); it->operator++()) {
        
        if (textViewRowNum > maxHeight) break;
        
        c = it->operator*();
        
        if (textViewColumnNum > maxWidth) {
            textViewColumnNum = 1;
            ++textViewRowNum;
            if (textViewRowNum > maxHeight) break;
            if (c == '\n') continue;
        }
        
        terminalViewController.print(c, convertTextPosnToTerminalPosn(Posn {textViewColumnNum, textViewRowNum}));
        
        if (c == '\n') {
            textViewColumnNum = 1;
            ++textViewRowNum;
        } else ++textViewColumnNum;
    }
    
    for (; textViewRowNum <= maxHeight; ++textViewRowNum) {
        if (textViewRowNum != 1) terminalViewController.print('~', convertTextPosnToTerminalPosn(Posn {1, textViewRowNum}));
    }
}

/* Returns 0 if the end of the text can be displayed. 1 if the end of the text cannot be displayed but no line is cut off, -1 otherwise */
int VmTextView::checkEndOfDisplay(const ConstTextIterator &itAtBeginningOfFirstDisplayedTextRow, const ConstTextIterator &end) {
    int textViewRowNum = 1;
    int textViewColumnNum = 1;
    char c;
    auto it = itAtBeginningOfFirstDisplayedTextRow.clone();
    for (; it->operator!=(end); it->operator++()) {
        
        if (textViewRowNum > maxHeight) break;
        
        c = it->operator*();
        
        if (textViewColumnNum > maxWidth) {
            ++textViewRowNum;
            if (textViewRowNum > maxHeight) break;
            textViewColumnNum = 1;
            if (c == '\n') continue;
        }
        
        if (c == '\n') {
            textViewColumnNum = 1;
            ++textViewRowNum;
        } else ++textViewColumnNum;
    }
    
    return it->operator=(end) ? 0 : textViewColumnNum > 1 ? -1 : 1;
}

VmTextView::~VmTextView() {}

