#include "VmEditor.h"
#include "VmText.h"
#include "VmCursor.h"

VmEditor::VmEditor(): text{std::make_unique<VmText>()} {}

VmEditor::VmEditor(std::unique_ptr<Text> text): text{std::move(text)} {}

const Text &VmEditor::getText() const { return *text; }

std::unique_ptr<Cursor> VmEditor::insertCharAt(char c, Cursor &cursor) {
    return std::unique_ptr<Cursor> {new VmCursor {*text}};
}

std::unique_ptr<Cursor> VmEditor::removeCharAt(char c, Cursor &cursor) {
    return std::unique_ptr<Cursor> {new VmCursor {*text}};
}

std::unique_ptr<Cursor> VmEditor::getForwardMatch(const Cursor &cursor, const std::string &s) const {
    return std::unique_ptr<Cursor> {new VmCursor {*text}};
}

std::unique_ptr<Cursor> VmEditor::getBackwardMatch(const Cursor &cursor, const std::string &s) const {
    return std::unique_ptr<Cursor> {new VmCursor {*text}};
}

std::unique_ptr<Cursor> VmEditor::goToStartOfFirstWordOfLine(const Cursor &cursor) const {
    auto newCursor = cursor.clone();
    if (newCursor->get() != '\n') {
        for (; isspace(newCursor->get()) && newCursor->next() != '\n'; newCursor->moveRightByOne()) {}
    }
    return newCursor;
}

VmEditor::~VmEditor() {}
