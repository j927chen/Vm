#include "VmCursor.h"
#include "Text.h"

VmCursor::VmCursor(const Text &text): text{text}, it{text.begin()}, textPosn{getInitialPosn()}, unboundedPosn{getInitialPosn()} {}

const Posn VmCursor::getInitialPosn() {
    return text.isEmpty() ? Posn {} : text.getLength() == 1 ? Posn {0, 1} : Posn {1, 1};
}

const Posn VmCursor::getPosn() const { return textPosn; }

void VmCursor::moveLeftByOne() {
    if (textPosn.y == 0 || textPosn.x <= 1) return;
    textPosn = Posn{textPosn.x - 1, textPosn.y};
    unboundedPosn = textPosn;
    it->operator--();
}

void VmCursor::moveRightByOne() {
    if (textPosn.y == 0 || textPosn.x == 0) return;
    if (it->operator++()->operator*() == '\n') {
        it->operator--();
        return;
    }
    textPosn = Posn{textPosn.x + 1, textPosn.y};
    unboundedPosn = Posn{unboundedPosn.x + 1, unboundedPosn.y};
}

void VmCursor::moveUpByOne() {
    if (textPosn.y <= 1) return;
    int newLineCount = 0;
    it = text.begin();
    while (newLineCount < textPosn.y - 2) {
        if (it->operator*() == '\n') ++newLineCount;
        it->operator++();
    }
    if (it->operator*() == '\n') {
        textPosn = Posn {0, textPosn.y - 1};
    } else {
        for (int i = 1; i <= unboundedPosn.x; ++i) {
            if (it->next()->operator*() == '\n' || i == unboundedPosn.x) {
                textPosn = Posn {i, textPosn.y - 1};
            }
            it->operator++();
        }
    }
    unboundedPosn = Posn {unboundedPosn.x, unboundedPosn.y - 1};
}

void VmCursor::moveDownByOne() {
    if (textPosn.y == text.getNumOfLines()) return;
    int newLineCount = 0;
    it = text.begin();
    while (newLineCount < textPosn.y) {
        if (it->operator*() == '\n') ++newLineCount;
        it->operator++();
    }
    if (it->operator*() == '\n') {
        textPosn = Posn {0, textPosn.y + 1};
    } else {
        for (int i = 1; i <= unboundedPosn.x; ++i) {
            if (it->next()->operator*() == '\n' || i == unboundedPosn.x) {
                textPosn = Posn {i, textPosn.y + 1};
            }
            it->operator++();
        }
    }
    unboundedPosn = Posn {unboundedPosn.x, unboundedPosn.y + 1};
}

void VmCursor::setPosn(const Posn p) {
    
}

VmCursor::~VmCursor() {}
