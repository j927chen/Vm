#include "VmTextView.h"
#include "TerminalViewController.h"
#include "Text.h"
#include "Update.h"
#include "Posn.h"

#include <iostream>

VmTextView::VmTextView(TerminalViewController &terminalViewController): View{terminalViewController}, firstDisplayedTextRowNum{1}, maxWidth{terminalViewController.getScrWidth()}, maxHeight{terminalViewController.getScrHeight() - 1} {}

const Posn VmTextView::convertTextPosnToTerminalPosn(const Posn p) {
    return Posn{p.x ? p.x - 1 : 0, p.y ? p.y - 1 : 0};
}

int VmTextView::getMinRelativeTextViewRowNum(int textLineNum, const Text &text) const {
    int currTextLineNum = firstDisplayedTextRowNum;
    int textViewRowNum = 1;
    int textViewColumnNum = 1;
    for (auto it = text.beginAtLine(firstDisplayedTextRowNum); currTextLineNum < textLineNum; it->operator++()) {
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

int VmTextView::getMaxRelativeTextViewRowNum(int textLineNum, const Text &text) const {
    int currTextLineNum = firstDisplayedTextRowNum;
    int textViewRowNum = 1;
    int textViewColumnNum = 1;
    for (auto it = text.beginAtLine(firstDisplayedTextRowNum); currTextLineNum <= textLineNum; it->operator++()) {
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

void VmTextView::accept(const NoUpdate &u) {}

void VmTextView::accept(const VmLoadFile &u) {
    display(*u.text.beginAtLine(firstDisplayedTextRowNum).get(), *u.text.end().get());
    moveCursor(u.cursorPosn.x, getMinRelativeTextViewRowNum(u.cursorPosn.y, u.text));
}

void VmTextView::accept(const VmCommandMode &u) {
    moveCursor(u.cursorPosn.x, getMinRelativeTextViewRowNum(u.cursorPosn.y, u.text));
}

void VmTextView::accept(const VmCommandEnterMode &u) {}

void VmTextView::accept(const VmMoveCursorUp &u) {
    if (firstDisplayedTextRowNum > 1 && getMinRelativeTextViewRowNum(u.cursorPosn.y, u.text) <= 5) {
        --firstDisplayedTextRowNum;
        display(*u.text.beginAtLine(firstDisplayedTextRowNum).get(), *u.text.end().get());
    }
    moveCursor(u.cursorPosn.x, getMinRelativeTextViewRowNum(u.cursorPosn.y, u.text));
}

void VmTextView::accept(const VmMoveCursorDown &u) {
    if (!displaysEndOfText && getMaxRelativeTextViewRowNum(u.cursorPosn.y, u.text) >= maxHeight - 4) {
        ++firstDisplayedTextRowNum;
        display(*u.text.beginAtLine(firstDisplayedTextRowNum).get(), *u.text.end().get());
    }
    moveCursor(u.cursorPosn.x, getMinRelativeTextViewRowNum(u.cursorPosn.y, u.text));
}

void VmTextView::accept(const VmMoveCursorLeft &u) {
    moveCursor(u.cursorPosn.x, getMinRelativeTextViewRowNum(u.cursorPosn.y, u.text));
}

void VmTextView::accept(const VmMoveCursorRight &u) {
    moveCursor(u.cursorPosn.x, getMinRelativeTextViewRowNum(u.cursorPosn.y, u.text));
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
    
    displaysEndOfText = it->operator=(end);
}

VmTextView::~VmTextView() {}

