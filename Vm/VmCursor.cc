#include "VmCursor.h"
#include "Text.h"

VmCursor::VmCursor(const Text &text): text{text}, it{text.begin()}, textPosn{getInitialPosn()}, unboundedPosn{getInitialPosn()} {}

VmCursor::VmCursor(const VmCursor &other): text{other.text}, it{other.it->clone()}, textPosn{other.textPosn}, unboundedPosn{other.unboundedPosn} {}

const Posn VmCursor::getInitialPosn() {
    return text.isEmpty() ? Posn {} : text.getLength() == 1 ? Posn {0, 1} : Posn {1, 1};
}

const Posn VmCursor::getPosn() const { return textPosn; }

char VmCursor::get() const { return it->operator*(); }

char VmCursor::next() const { return it->next()->operator*(); }

void VmCursor::moveLeftByOne() {
    if (textPosn.y == 0 || textPosn.x <= 1) return;
    textPosn = Posn{textPosn.x - 1, textPosn.y};
    unboundedPosn = textPosn;
    it->operator--();
}

void VmCursor::moveRightByOne() {
    if (textPosn.y == 0 || textPosn.x == 0) return;
    if (it->next()->operator*() == '\n') {
        return;
    }
    it->operator++();
    textPosn = Posn{textPosn.x + 1, textPosn.y};
    unboundedPosn = Posn{unboundedPosn.x + 1, unboundedPosn.y};
}

void VmCursor::moveUpByOne() {
    if (textPosn.y <= 1) return;
    it = text.beginAtLine(textPosn.y - 1);
    if (it->operator*() == '\n') {
        textPosn = Posn {0, textPosn.y - 1};
    } else {
        --textPosn.y;
        for (textPosn.x = 1; textPosn.x < unboundedPosn.x; ++textPosn.x) {
            if (it->next()->operator*() == '\n') break;
            it->operator++();
        }
    }
    unboundedPosn = Posn {unboundedPosn.x, unboundedPosn.y - 1};
}

void VmCursor::moveDownByOne() {
    if (textPosn.y == text.getNumOfLines()) return;
    it = text.beginAtLine(textPosn.y + 1);
    if (it->operator*() == '\n') {
        textPosn = Posn {0, textPosn.y + 1};
    } else {
        ++textPosn.y;
        for (textPosn.x = 1; textPosn.x < unboundedPosn.x; ++textPosn.x) {
            if (it->next()->operator*() == '\n') break;
            it->operator++();
        }
    }
    unboundedPosn = Posn {unboundedPosn.x, unboundedPosn.y + 1};
}

void VmCursor::setPosn(const Posn p) {
    if (p.y == 0) {
        it = text.begin();
        if (text.isEmpty()) textPosn = Posn {};
        else textPosn = Posn {it->operator*() == '\n' ? 0 : 1, 1};
    } else if (p.y > text.getNumOfLines()){
        it = text.goBackToStartOfPreviousLine(*text.end());
        textPosn = Posn {it->operator*() == '\n' ? 0 : 1, text.getNumOfLines()};
    } else {
        it = text.beginAtLine(p.y);
        textPosn = Posn {it->operator*() == '\n' ? 0 : 1, p.y};
    }
    unboundedPosn = textPosn;
}

std::unique_ptr<Cursor> VmCursor::clone() const {
    return std::make_unique<VmCursor>(*this);
}

VmCursor::~VmCursor() {}
