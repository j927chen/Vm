#include "VmModel.h"
#include "Text.h"
#include "Reader.h"
#include "Writer.h"
#include "Posn.h"
#include "Update.h"
#include "Cursor.h"

VmModel::VmModel(std::unique_ptr<Text> text, std::unique_ptr<Cursor> cursor, std::unique_ptr<Reader> reader, std::unique_ptr<Writer> writer): text{std::move(text)}, cursor{std::move(cursor)}, reader{std::move(reader)}, writer{std::move(writer)} {}

std::unique_ptr<const Update> VmModel::update(const unknownKeyPressed &a) {
    return std::unique_ptr<const VmMoveCursorRight>(new VmMoveCursorRight {*text, cursor->getPosn()});
}

std::unique_ptr<const Update> VmModel::update(const hKeyPressed &a) {
    cursor->moveLeftByOne();
    return std::unique_ptr<const VmMoveCursorLeft>(new VmMoveCursorLeft {*text, cursor->getPosn()});
}

std::unique_ptr<const Update> VmModel::update(const jKeyPressed &a) {
    cursor->moveDownByOne();
    return std::unique_ptr<const VmMoveCursorDown>(new VmMoveCursorDown {*text, cursor->getPosn()});
}

std::unique_ptr<const Update> VmModel::update(const kKeyPressed &a) {
    cursor->moveUpByOne();
    return std::unique_ptr<const VmMoveCursorUp>(new VmMoveCursorUp {*text, cursor->getPosn()});
}

std::unique_ptr<const Update> VmModel::update(const lKeyPressed &a) {
    cursor->moveRightByOne();
    return std::unique_ptr<const VmMoveCursorRight>(new VmMoveCursorRight {*text, cursor->getPosn()});
}

std::unique_ptr<const Update> VmModel::update(const escKeyPressed &a) {
    return std::unique_ptr<const VmMoveCursorRight>(new VmMoveCursorRight {*text, cursor->getPosn()});
}

const Text &VmModel::getText() { return *text; }
const Cursor &VmModel::getCursor() { return *cursor; }

VmModel::~VmModel() {}
