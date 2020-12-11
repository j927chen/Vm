#include "Update.h"
#include "View.h"

Update::~Update() {}

VmLoadFile::VmLoadFile(const std::string &fileName, const Posn cursorPosn, const Text &text): fileName{fileName}, cursorPosn{cursorPosn}, text{text} {}

void VmLoadFile::visit(View &v) const { v.accept(*this); }

VmLoadFile::~VmLoadFile() {}

VmMoveCursor::VmMoveCursor(const Text &text, const Posn cursorPosn): text{text}, cursorPosn{cursorPosn} {}

VmMoveCursor::~VmMoveCursor() {}

VmMoveCursorUp::VmMoveCursorUp(const Text &text, const Posn cursorPosn): VmMoveCursor{text, cursorPosn} {}

void VmMoveCursorUp::visit(View &v) const { v.accept(*this); }

VmMoveCursorUp::~VmMoveCursorUp() {}

VmMoveCursorDown::VmMoveCursorDown(const Text &text, const Posn cursorPosn): VmMoveCursor{text, cursorPosn} {}

void VmMoveCursorDown::visit(View &v) const { v.accept(*this); }

VmMoveCursorDown::~VmMoveCursorDown() {}

VmMoveCursorLeft::VmMoveCursorLeft(const Text &text, const Posn cursorPosn): VmMoveCursor{text, cursorPosn} {}

void VmMoveCursorLeft::visit(View &v) const { v.accept(*this); }

VmMoveCursorLeft::~VmMoveCursorLeft() {}

VmMoveCursorRight::VmMoveCursorRight(const Text &text, const Posn cursorPosn): VmMoveCursor{text, cursorPosn} {}

void VmMoveCursorRight::visit(View &v) const { v.accept(*this); }

VmMoveCursorRight::~VmMoveCursorRight() {}



