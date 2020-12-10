#include <string>
#include "Update.h"
#include "View.h"

Update::~Update() {}

VmLoadFile::VmLoadFile(const std::string &filename, const Text &text): fileName{fileName}, text{text} {}

void VmLoadFile::visit(View &v) const { v.accept(*this); }

VmLoadFile::~VmLoadFile() {}

VmMoveCursor::VmMoveCursor(const Text &text, const Posn cursorPosn): text{text}, cursorPosn{cursorPosn} {}

VmMoveCursor::~VmMoveCursor() {}

VmMoveCursorDown::VmMoveCursorDown(const Text &text, const Posn cursorPosn): VmMoveCursor{text, cursorPosn} {}

void VmMoveCursorDown::visit(View &v) const { v.accept(*this); }

VmMoveCursorDown::~VmMoveCursorDown() {}

VmMoveCursorLeft::VmMoveCursorLeft(const Text &text, const Posn cursorPosn): VmMoveCursor{text, cursorPosn} {}

void VmMoveCursorLeft::visit(View &v) const { v.accept(*this); }

VmMoveCursorLeft::~VmMoveCursorLeft() {}

VmMoveCursorRight::VmMoveCursorRight(const Text &text, const Posn cursorPosn): VmMoveCursor{text, cursorPosn} {}

void VmMoveCursorRight::visit(View &v) const { v.accept(*this); }

VmMoveCursorRight::~VmMoveCursorRight() {}



