#include "VmModel.h"
#include "Text.h"
#include "Reader.h"
#include "Writer.h"
#include "Update.h"

VmModel::VmModel(std::unique_ptr<Text> text, std::unique_ptr<Reader> reader, std::unique_ptr<Writer> writer): text{std::move(text)}, reader{std::move(reader)}, writer{std::move(writer)} {}

std::unique_ptr<const Update> VmModel::update(const unknownKeyPressed &a) {
    return std::make_unique<const VmMoveCursorDown>(*text.get(), *text->cbegin().get());
}
std::unique_ptr<const Update> VmModel::update(const hKeyPressed &a) {
    return std::make_unique<const VmMoveCursorLeft>(*text.get(), *text->cbegin().get());
}
std::unique_ptr<const Update> VmModel::update(const escKeyPressed &a) {
    return std::make_unique<const VmMoveCursorDown>(*text.get(), *text->cbegin().get());
}

const Text &VmModel::getText() { return *text.get(); }

VmModel::~VmModel() {}
