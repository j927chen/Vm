#include "Update.h"
#include "View.h"

Update::~Update() {}

void NoUpdate::visit(View &v) const { v.accept(*this); }

NoUpdate::~NoUpdate() {}


Terminate::~Terminate() {}

void Terminate::visit(View &v) const {}


VmLoadFile::VmLoadFile(const std::string &fileName, const Cursor &cursor, const Text &text): fileName{fileName}, cursor{cursor}, text{text} {}

void VmLoadFile::visit(View &v) const { v.accept(*this); }

VmLoadFile::~VmLoadFile() {}

// - MARK: Mode

VmCommandMode::VmCommandMode(const Cursor &cursor, const Posn previousCursorPosn, const std::string message): VmMoveCursor(cursor, std::move(previousCursorPosn)), message{std::move(message)} {}

void VmCommandMode::visit(View &v) const { v.accept(*this); }

VmCommandMode::~VmCommandMode() {}


VmCommandEnterMode::VmCommandEnterMode(const std::string &typedCommand): typedCommand(typedCommand) {}

void VmCommandEnterMode::visit(View &v) const { v.accept(*this); }

VmCommandEnterMode::~VmCommandEnterMode() {}


VmInsertMode::VmInsertMode(const Cursor &cursor, const Posn previousCursorPosn): VmMoveCursor(cursor, std::move(previousCursorPosn)) {}

void VmInsertMode::visit(View &v) const { v.accept(*this); }

VmInsertMode::~VmInsertMode() {}


VmMultiplier::VmMultiplier(int multiplier): multiplier{multiplier} {}

void VmMultiplier::visit(View &v) const { v.accept(*this); }

VmMultiplier::~VmMultiplier() {}


// - MARK: Cursor

VmMoveCursor::VmMoveCursor(const Cursor &cursor, const Posn previousCursorPosn): cursor{cursor}, previousCursorPosn{previousCursorPosn} {}

void VmMoveCursor::visit(View &v) const { v.accept(*this); }

VmMoveCursor::~VmMoveCursor() {}

VmMoveCursorUp::VmMoveCursorUp(const Cursor &cursor, const Posn previousCursorPosn): VmMoveCursor{cursor, previousCursorPosn} {}

void VmMoveCursorUp::visit(View &v) const { v.accept(*this); }

VmMoveCursorUp::~VmMoveCursorUp() {}

VmMoveCursorDown::VmMoveCursorDown(const Cursor &cursor, const Posn previousCursorPosn): VmMoveCursor{cursor, previousCursorPosn} {}

void VmMoveCursorDown::visit(View &v) const { v.accept(*this); }

VmMoveCursorDown::~VmMoveCursorDown() {}

VmMoveCursorLeft::VmMoveCursorLeft(const Cursor &cursor, const Posn previousCursorPosn): VmMoveCursor{cursor, previousCursorPosn} {}

void VmMoveCursorLeft::visit(View &v) const { v.accept(*this); }

VmMoveCursorLeft::~VmMoveCursorLeft() {}

VmMoveCursorRight::VmMoveCursorRight(const Cursor &cursor, const Posn previousCursorPosn): VmMoveCursor{cursor, previousCursorPosn} {}

void VmMoveCursorRight::visit(View &v) const { v.accept(*this); }

VmMoveCursorRight::~VmMoveCursorRight() {}
