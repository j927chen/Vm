#include "VmCursor.h"
#include "Text.h"

VmCursor::VmCursor(const Text &text): text{text}, it{text.begin()}, textPosn{getInitialPosn()}, unboundedPosn{getInitialPosn()} {}

VmCursor::VmCursor(const VmCursor &other): text{other.text}, it{other.it->clone()}, textPosn{other.textPosn}, unboundedPosn{other.unboundedPosn} {}

VmCursor::VmCursor(const Text &text, const ConstTextIterator &it): text{text}, it{text.begin()}, textPosn{text.isEmpty() ? Posn {} : Posn {1, 1}} {
    for (; this->it->operator!=(*text.end()); this->it->operator++()) {
        if (this->it->operator==(it)) break;
        if (this->it->operator*() == '\n') {
            textPosn.x = 1;
            ++textPosn.y;
        } else ++textPosn.x;
    }
    unboundedPosn = textPosn;
}

const Posn VmCursor::getInitialPosn() {
    return text.isEmpty() ? Posn {} : text.getLength() == 1 ? Posn {0, 1} : Posn {1, 1};
}

const Posn VmCursor::getPosn() const { return textPosn; }

char VmCursor::get() const { return it->operator*(); }

char VmCursor::getNext() const { return it->next()->operator*(); }

const Text &VmCursor::getText() const { return text; }

const ConstTextIterator &VmCursor::getIt() const { return *it; }

void VmCursor::moveLeftByOne() {
    if (textPosn.y == 0 || textPosn.x <= 1) return;
    textPosn = Posn{textPosn.x - 1, textPosn.y};
    unboundedPosn = textPosn;
    it->operator--();
}

void VmCursor::moveRightByOne() {
    if (textPosn.y == 0 || textPosn.x == 0) return;
    if (it->operator*() == '\n') return;
    it->operator++();
    ++textPosn.x;
    ++unboundedPosn.x;
}

void VmCursor::moveRightByOneNoNewLine() {
    if (textPosn.y == 0 || textPosn.x == 0) return;
    if (it->operator*() == '\n' || it->next()->operator*() == '\n') return;
    it->operator++();
    ++textPosn.x;
    ++unboundedPosn.x;
}

void VmCursor::moveUpByOne() {
    if (textPosn.y <= 1) return;
    it = text.beginAtLine(textPosn.y - 1);
    --textPosn.y;
    if (it->operator*() == '\n') {
        textPosn.x = 1;
    } else {
        for (textPosn.x = 1; textPosn.x < unboundedPosn.x; ++textPosn.x) {
            if (it->operator*() == '\n') break;
            it->operator++();
        }
    }
    unboundedPosn = Posn {unboundedPosn.x, unboundedPosn.y - 1};
}

void VmCursor::moveUpByOneNoNewLine() {
    if (textPosn.y <= 1) return;
    it = text.beginAtLine(textPosn.y - 1);
    --textPosn.y;
    if (it->operator*() == '\n') {
        textPosn.x = 1;
    } else {
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
    ++textPosn.y;
    if (it->operator*() == '\n') {
        textPosn.x = 1;
    } else {
        for (textPosn.x = 1; textPosn.x < unboundedPosn.x; ++textPosn.x) {
            if (it->operator*() == '\n') break;
            it->operator++();
        }
    }
    unboundedPosn = Posn {unboundedPosn.x, unboundedPosn.y + 1};
}


void VmCursor::moveDownByOneNoNewLine() {
    if (textPosn.y == text.getNumOfLines()) return;
    it = text.beginAtLine(textPosn.y + 1);
    ++textPosn.y;
    if (it->operator*() == '\n') {
        textPosn.x = 1;
    } else {
        for (textPosn.x = 1; textPosn.x < unboundedPosn.x; ++textPosn.x) {
            if (it->next()->operator*() == '\n') break;
            it->operator++();
        }
    }
    unboundedPosn = Posn {unboundedPosn.x, unboundedPosn.y + 1};
}

void VmCursor::setPosn(const Posn p) {
    if (text.isEmpty()) textPosn = Posn {};
    else {
        if (p.y == 0) {
            it = text.begin();
            textPosn = Posn {1, 1};
        } else if (p.y > text.getNumOfLines()){
            it = text.goBackToStartOfPreviousLine(*text.end());
            textPosn = Posn {1, text.getNumOfLines()};
        } else {
            it = text.beginAtLine(p.y);
            textPosn = Posn {1, p.y};
        }
    }
    unboundedPosn = textPosn;
}

void VmCursor::resetUnboundedPosn() { unboundedPosn = textPosn; }

std::unique_ptr<Cursor> VmCursor::clone() const {
    return std::make_unique<VmCursor>(*this);
}

std::unique_ptr<Cursor> VmCursor::clonePrevious() const {
    return std::make_unique<VmCursor>(text, *it->previous());
}

VmCursor::~VmCursor() {}
