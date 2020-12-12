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

std::unique_ptr<Cursor> VmEditor::getForwardMatch(Cursor &cursor, const std::string &s) const {
    return std::unique_ptr<Cursor> {new VmCursor {*text}};
}

std::unique_ptr<Cursor> VmEditor::getBackwardMatch(Cursor &cursor, const std::string &s) const {
    return std::unique_ptr<Cursor> {new VmCursor {*text}};
}

VmEditor::~VmEditor() {}
