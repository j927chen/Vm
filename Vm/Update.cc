#include <string>
#include "Update.h"
#include "View.h"

Update::~Update() {}

VmLoadFile::VmLoadFile(const std::string &filename, const Text &text): fileName{fileName}, text{text} {}

void VmLoadFile::visit(View &v) { v.accept(*this); }

VmLoadFile::~VmLoadFile() {}

VmMoveCursor::VmMoveCursor(const Text &text, ConstTextIterator &constTextIterator): text{text}, constTextIterator{constTextIterator} {}

VmMoveCursor::~VmMoveCursor() {}

VmMoveCursorDown::VmMoveCursorDown(const Text &text, ConstTextIterator &constTextIterator): VmMoveCursor{text, constTextIterator} {}

void VmMoveCursorDown::visit(View &v) { v.accept(*this); }

VmMoveCursorDown::~VmMoveCursorDown() {}

VmMoveCursorLeft::VmMoveCursorLeft(const Text &text, ConstTextIterator &constTextIterator): VmMoveCursor{text, constTextIterator} {}

void VmMoveCursorLeft::visit(View &v) { v.accept(*this); }

VmMoveCursorLeft::~VmMoveCursorLeft() {}



