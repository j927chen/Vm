#include <algorithm>
#include "VmModel.h"
#include "VmEditor.h"
#include "VmText.h"
#include "VmCursor.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "Action.h"
#include "Update.h"

VmModel::VmModel(): fileName{""}, mode{COMMAND}, editor{std::make_unique<VmEditor>()}, cursor{std::make_unique<VmCursor>(editor->getText())}, reader{std::make_unique<FileReader>()}, writer{std::make_unique<FileWriter>()} {}

VmModel::VmModel(std::string fileName): fileName{std::move(fileName)}, mode{COMMAND}, reader{std::make_unique<FileReader>()}, writer{std::make_unique<FileWriter>()} {
    editor = std::make_unique<VmEditor>(reader->read(this->fileName));
    cursor = std::make_unique<VmCursor>(editor->getText());
}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const otherKeyPressed> a) {
    switch (mode) {
        case COMMAND:
            return std::make_unique<NoUpdate>();
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand(a->code);
        case INSERT:
            return std::make_unique<NoUpdate>();
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const enterKeyPressed> a) {
    switch (mode) {
        case COMMAND:
            return std::make_unique<NoUpdate>();
        case COMMAND_ENTER:
            return updateForTypedCommand();
        case INSERT:
            return std::make_unique<NoUpdate>();
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const colonKeyPressed> a) {
    switch (mode) {
        case COMMAND:
            mode = COMMAND_ENTER;
            return pushBackCharInTypedCommand(':');
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand(':');
        case INSERT:
            return std::make_unique<NoUpdate>();
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const hKeyPressed> a) {
    switch (mode) {
        case COMMAND:
            cursor->moveLeftByOne();
            return std::make_unique<VmMoveCursorLeft>(editor->getText(), cursor->getPosn());
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand('h');
        case INSERT:
            return std::make_unique<NoUpdate>();
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const jKeyPressed> a) {
    switch (mode) {
        case COMMAND:
            cursor->moveDownByOne();
            return std::make_unique<VmMoveCursorDown>(editor->getText(), cursor->getPosn());
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand('j');
        case INSERT:
            return std::make_unique<NoUpdate>();
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const kKeyPressed> a) {
    switch (mode) {
        case COMMAND:
            cursor->moveUpByOne();
            return std::make_unique<VmMoveCursorUp>(editor->getText(), cursor->getPosn());
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand('k');
        case INSERT:
            return std::make_unique<NoUpdate>();
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }

}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const lKeyPressed> a) {
    switch (mode) {
        case COMMAND:
            cursor->moveRightByOne();
            return std::unique_ptr<const VmMoveCursorRight>(new VmMoveCursorRight {editor->getText(), cursor->getPosn()});
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand('l');
        case INSERT:
            return std::make_unique<NoUpdate>();
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const escKeyPressed> a) {
    switch (mode) {
        case COMMAND:
            return std::make_unique<NoUpdate>();
        case COMMAND_ENTER:
            typedCommand = "";
            mode = COMMAND;
            return std::make_unique<VmCommandMode>(editor->getText(), cursor->getPosn());
        case INSERT:
            return std::make_unique<NoUpdate>();
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const backspaceKeyPressed> a) {
    switch (mode) {
        case COMMAND:
            return std::make_unique<const NoUpdate>();
        case COMMAND_ENTER:
            typedCommand.pop_back();
            if (typedCommand.empty()) {
                mode = COMMAND;
                return std::make_unique<const VmCommandMode>(editor->getText(), cursor->getPosn());
            }
            return std::make_unique<VmCommandEnterMode>(typedCommand);
        case INSERT:
            return std::make_unique<NoUpdate>();
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

const std::string &VmModel::getFileName() const { return fileName; }
const Editor &VmModel::getEditor() const { return *editor; }
const Cursor &VmModel::getCursor() const { return *cursor; }

std::unique_ptr<const Update> VmModel::pushBackCharInTypedCommand(char c) {
    typedCommand.push_back(c);
    return std::make_unique<VmCommandEnterMode>(typedCommand);
}

std::unique_ptr<const Update> VmModel::updateForTypedCommand() {
    auto update = parseColonCommand()->visit(*this);
    mode = COMMAND;
    typedCommand.erase();
    return update;
}

const std::unique_ptr<const VmModel::colonCommand> VmModel::parseColonCommand() const {
    // remove the spaces from the input
    std::string typedCommandCopy = typedCommand;
    typedCommandCopy.erase(remove_if(typedCommandCopy.begin(), typedCommandCopy.end(), isspace), typedCommandCopy.end());

    if (!typedCommandCopy.compare(":w")) return std::make_unique<const colon_w>();
    if (!typedCommandCopy.compare(":q")) return std::make_unique<const colon_q>();
    if (!typedCommandCopy.compare(":q!")) return std::make_unique<const colon_q_exclaimation_mark>();
    if (!typedCommandCopy.compare(":wq")) return std::make_unique<const colon_wq>();
    if (!typedCommandCopy.compare(":r")) return std::make_unique<const colon_r>();
    if (!typedCommandCopy.compare(":$")) return std::make_unique<const colon_dollar_sign>();
    return std::make_unique<const colon_number>(std::stoi(typedCommandCopy.substr(1, typedCommandCopy.length() - 1)));
}

std::unique_ptr<const Update> VmModel::update(colon_q c) {
    // CHECK IF FILE IS MODIFIED
    return std::make_unique<const Terminate>();
}

std::unique_ptr<const Update> VmModel::update(colon_q_exclaimation_mark c) {
    return std::make_unique<const Terminate>();
}

std::unique_ptr<const Update> VmModel::update(colon_w c) {
    try {
        writer->write(fileName, editor->getText());
    } catch (Writer::invalidPath) {
        return std::make_unique<const VmCommandMode>(editor->getText(), cursor->getPosn());
    }
    return std::make_unique<const VmLoadFile>(fileName, cursor->getPosn(), editor->getText());
}

std::unique_ptr<const Update> VmModel::update(colon_wq c) {
    try {
        writer->write(fileName, editor->getText());
    } catch (Writer::invalidPath) {
        return std::make_unique<const VmCommandMode>(editor->getText(), cursor->getPosn());
    }
    return std::make_unique<const Terminate>();
}

std::unique_ptr<const Update> VmModel::update(colon_r c) {
    // INSERT TEXT BELOW CURSOR
    return std::make_unique<const VmCommandMode>(editor->getText(), cursor->getPosn());
}

std::unique_ptr<const Update> VmModel::update(colon_dollar_sign c) {
    // GO TO LAST LINE
    return std::make_unique<const VmCommandMode>(editor->getText(), cursor->getPosn());
}

std::unique_ptr<const Update> VmModel::update(colon_number c) {
    // GO TO SPECIFIED LINE AFTER CHECKING RANGE
    return std::make_unique<const VmCommandMode>(editor->getText(), cursor->getPosn());
}


VmModel::~VmModel() {}



// MARK: Colon Commands

VmModel::colonCommand::~colonCommand() {}

std::unique_ptr<const Update> VmModel::colon_q::visit(VmModel &m) const {
    return m.update(*this);
}


VmModel::colon_q::~colon_q() {}

std::unique_ptr<const Update> VmModel::colon_q_exclaimation_mark::visit(VmModel &m) const {
    return m.update(*this);
}

VmModel::colon_q_exclaimation_mark::~colon_q_exclaimation_mark() {}


std::unique_ptr<const Update> VmModel::colon_w::visit(VmModel &m) const {
    return m.update(*this);
}


VmModel::colon_w::~colon_w() {}

std::unique_ptr<const Update> VmModel::colon_wq::visit(VmModel &m) const {
    return m.update(*this);
}

VmModel::colon_wq::~colon_wq() {}


std::unique_ptr<const Update> VmModel::colon_r::visit(VmModel &m) const {
    return m.update(*this);
}

VmModel::colon_r::~colon_r() {}


std::unique_ptr<const Update> VmModel::colon_dollar_sign::visit(VmModel &m) const {
    return m.update(*this);
}

VmModel::colon_dollar_sign::~colon_dollar_sign() {}


VmModel::colon_number::colon_number(int ln): ln{ln} {}

std::unique_ptr<const Update> VmModel::colon_number::visit(VmModel &m) const {
    return m.update(*this);
}

VmModel::colon_number::~colon_number() {}
