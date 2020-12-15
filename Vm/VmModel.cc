#include <algorithm>
#include "VmModel.h"
#include "VmEditor.h"
#include "VmText.h"
#include "VmCursor.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "Action.h"
#include "Update.h"

VmModel::VmModel(): fileName{""}, mode{COMMAND}, editor{std::make_unique<VmEditor>()}, cursor{std::make_unique<VmCursor>(editor->getText())}, reader{std::make_unique<FileReader>()}, writer{std::make_unique<FileWriter>()}, typedCommand{""}, multiplier{0} {}

VmModel::VmModel(std::string fileName): fileName{std::move(fileName)}, mode{COMMAND}, reader{std::make_unique<FileReader>()}, writer{std::make_unique<FileWriter>()}, typedCommand{""}, multiplier{0} {
    editor = std::make_unique<VmEditor>(reader->read(this->fileName));
    cursor = std::make_unique<VmCursor>(editor->getText());
}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const otherKeyPressed> a) {
    switch (mode) {
        case COMMAND:
            return std::make_unique<NoUpdate>();
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand(a->code);
        case INSERT: {
            const Posn previousCursorPosn = cursor->getPosn();
            cursor = editor->insertCharAt(a->code, *cursor);
            return defaultInsertUpdate(std::move(previousCursorPosn));
        }
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const numberKeyPressed> a) {
    switch (mode) {
        case COMMAND: {
            if (multiplier == 0 && a->num == 0) {
                // GO TO START OF LINE
                return std::make_unique<NoUpdate>();
            }
            multiplier = multiplier * 10 + a->num;
            return std::make_unique<const VmMultiplier>(multiplier);
        }
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand(a->num + '0');
        case INSERT: {
            const Posn previousCursorPosn = cursor->getPosn();
            cursor = editor->insertCharAt(a->num + '0', *cursor);
            return defaultInsertUpdate(std::move(previousCursorPosn));
        }
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

// MARK: - ^g

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const control_gKeyPressed> a) {
    switch (mode) {
        case COMMAND: {
            int numOfLines = editor->getText().getNumOfLines();
            const std::string message = std::string {'"'} + (fileName.empty() ? "[No Name]" : fileName) + std::string {'"'} + " " + (numOfLines == 0 ? "--No lines in buffer--" : numOfLines == 1 ? "1 line" : std::to_string(numOfLines) + " lines");
            return std::make_unique<const VmCommandMode>(*cursor, cursor->getPosn(),  message);
        }
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand(7);
        case INSERT: {
            const Posn previousCursorPosn = cursor->getPosn();
            cursor = editor->insertCharAt(7, *cursor);
            return defaultInsertUpdate(std::move(previousCursorPosn));
        }
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

// MARK: - enter

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const enterKeyPressed> a) {
    switch (mode) {
        case COMMAND:
            return std::make_unique<NoUpdate>();
        case COMMAND_ENTER:
            return updateForTypedCommand();
        case INSERT: {
            const Posn previousCursorPosn = cursor->getPosn();
            cursor = editor->insertCharAt('\n', *cursor);
            return defaultInsertUpdate(std::move(previousCursorPosn));
        }
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const colonKeyPressed> a) {
    switch (mode) {
        case COMMAND:
            mode = COMMAND_ENTER;
            multiplier = 0;
            return pushBackCharInTypedCommand(':');
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand(':');
        case INSERT: {
            const Posn previousCursorPosn = cursor->getPosn();
            cursor = editor->insertCharAt(':', *cursor);
            return defaultInsertUpdate(std::move(previousCursorPosn));
        }
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const forwardSlashKeyPressed> a) {
    switch (mode) {
        case COMMAND: {
            mode = COMMAND_ENTER;
            return pushBackCharInTypedCommand('/');
        }
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand('/');
        case INSERT: {
            const Posn previousCursorPosn = cursor->getPosn();
            cursor = editor->insertCharAt('/', *cursor);
            return defaultInsertUpdate(std::move(previousCursorPosn));
        }
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const questionMarkKeyPressed> a) {
    switch (mode) {
        case COMMAND: {
            mode = COMMAND_ENTER;
            return pushBackCharInTypedCommand('?');
        }
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand('?');
        case INSERT: {
            const Posn previousCursorPosn = cursor->getPosn();
            cursor = editor->insertCharAt('?', *cursor);
            return defaultInsertUpdate(std::move(previousCursorPosn));
        }
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

// MARK: - N

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const NKeyPressed> a) {
    switch (mode) {
        case COMMAND: {
            const Posn previousCursorPosn = cursor->getPosn();
            std::string message {};
            int loop = 0;
            try {
                auto previousSearchRequest = editor->getPreviousSearch();
                std::unique_ptr<Searchable::SearchResult> result;
                if (previousSearchRequest->forward) {
                    if (multiplier == 0) {
                        result = editor->getBackwardMatch(*cursor, previousSearchRequest->searchPattern);
                        cursor = std::move(result->cursor);
                        loop = result->loop;
                    }
                    for (; multiplier > 0; --multiplier) {
                        result = editor->getBackwardMatch(*cursor, previousSearchRequest->searchPattern);
                        cursor = std::move(result->cursor);
                        if (loop == 0) loop = result->loop;
                    }
                    // do not record this N command
                    editor->getForwardMatch(*cursor, previousSearchRequest->searchPattern);
                } else {
                    if (multiplier == 0) {
                        result = editor->getForwardMatch(*cursor, previousSearchRequest->searchPattern);
                        cursor = std::move(result->cursor);
                        loop = result->loop;
                    }
                    for (; multiplier > 0; --multiplier) {
                        result = editor->getForwardMatch(*cursor, previousSearchRequest->searchPattern);
                        cursor = std::move(result->cursor);
                        if (loop == 0) loop = result->loop;
                    }
                    editor->getBackwardMatch(*cursor, previousSearchRequest->searchPattern);
                }
                if (!result->matchFound) message = "Pattern not found";
                else if (loop == 1) message = "search hit BOTTOM, continuing at TOP";
                else if (loop == -1) message = "search hit TOP, continuing at BOTTOM";
            } catch (...) {
                message = "No previous regular expression";
                multiplier = 0;
            }
            return std::make_unique<const VmCommandMode>(*cursor, previousCursorPosn, message);
        }
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand('N');
        case INSERT: {
            const Posn previousCursorPosn = cursor->getPosn();
            cursor = editor->insertCharAt('N', *cursor);
            return defaultInsertUpdate(std::move(previousCursorPosn));
        }
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

// MARK: - h

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const hKeyPressed> a) {
    switch (mode) {
        case COMMAND: {
            const Posn previousCursorPosn = cursor->getPosn();
            if (multiplier == 0) cursor->moveLeftByOne();
            for (; multiplier > 0; --multiplier) cursor->moveLeftByOne();
            return std::make_unique<VmMoveCursorLeft>(*cursor, previousCursorPosn);
        }
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand('h');
        case INSERT: {
            const Posn previousCursorPosn = cursor->getPosn();
            cursor = editor->insertCharAt('h', *cursor);
            return defaultInsertUpdate(std::move(previousCursorPosn));
        }
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}
std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const iKeyPressed> a) {
    switch (mode) {
        case COMMAND: {
            mode = INSERT;
            // CHECK FOR MULTIPLIER
            return std::make_unique<const VmInsertMode>(*cursor, cursor->getPosn());
        }
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand('i');
        case INSERT: {
            const Posn previousCursorPosn = cursor->getPosn();
            cursor = editor->insertCharAt('i', *cursor);
            return defaultInsertUpdate(std::move(previousCursorPosn));
        }
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const jKeyPressed> a) {
    switch (mode) {
        case COMMAND: {
            Posn previousCursorPosn = cursor->getPosn();
            if (multiplier == 0) cursor->moveDownByOneNoNewLine();
            for (; multiplier > 0; --multiplier) cursor->moveDownByOneNoNewLine();
            return std::make_unique<VmMoveCursorDown>(*cursor, previousCursorPosn);
        }
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand('j');
        case INSERT: {
            const Posn previousCursorPosn = cursor->getPosn();
            cursor = editor->insertCharAt('j', *cursor);
            return defaultInsertUpdate(std::move(previousCursorPosn));
        }
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const kKeyPressed> a) {
    switch (mode) {
        case COMMAND: {
            const Posn previousCursorPosn = cursor->getPosn();
            if (multiplier == 0) cursor->moveUpByOneNoNewLine();
            for (; multiplier > 0; --multiplier) cursor->moveUpByOneNoNewLine();
            return std::make_unique<VmMoveCursorUp>(*cursor, previousCursorPosn);
        }
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand('k');
        case INSERT: {
            const Posn previousCursorPosn = cursor->getPosn();
            cursor = editor->insertCharAt('k', *cursor);
            return defaultInsertUpdate(std::move(previousCursorPosn));
        }
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }

}

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const lKeyPressed> a) {
    switch (mode) {
        case COMMAND: {
            const Posn previousCursorPosn = cursor->getPosn();
            if (multiplier == 0) cursor->moveRightByOneNoNewLine();
            for (; multiplier > 0; --multiplier) cursor->moveRightByOneNoNewLine();
            return std::unique_ptr<const VmMoveCursorRight>(new VmMoveCursorRight {*cursor, previousCursorPosn});
        }
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand('l');
        case INSERT: {
            const Posn previousCursorPosn = cursor->getPosn();
            cursor = editor->insertCharAt('l', *cursor);
            return defaultInsertUpdate(std::move(previousCursorPosn));
        }
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

// MARK: - n

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const nKeyPressed> a) {
    switch (mode) {
        case COMMAND: {
            const Posn previousCursorPosn = cursor->getPosn();
            std::string message {};
            try {
                auto previousSearchRequest = editor->getPreviousSearch();
                std::unique_ptr<Searchable::SearchResult> result;
                int loop = 0;
                if (previousSearchRequest->forward) {
                    if (multiplier == 0) {
                        result = editor->getForwardMatch(*cursor, previousSearchRequest->searchPattern);
                        cursor = std::move(result->cursor);
                        loop = result->loop;
                    }
                    for (; multiplier > 0; --multiplier) {
                        result = editor->getForwardMatch(*cursor, previousSearchRequest->searchPattern);
                        cursor = std::move(result->cursor);
                        if (loop == 0) loop = result->loop;
                    }
                    if (cursor->getPosn() == previousCursorPosn) {
                        result = editor->getForwardMatch(*cursor, previousSearchRequest->searchPattern);
                        cursor = std::move(result->cursor);
                    }
                } else {
                    if (multiplier == 0) {
                        result = editor->getBackwardMatch(*cursor, previousSearchRequest->searchPattern);
                        cursor = std::move(result->cursor);
                        loop = result->loop;
                    }
                    for (; multiplier > 0; --multiplier) {
                        result = editor->getBackwardMatch(*cursor, previousSearchRequest->searchPattern);
                        cursor = std::move(result->cursor);
                        if (loop == 0) loop = result->loop;
                    }
                    if (cursor->getPosn() == previousCursorPosn) {
                        result = editor->getBackwardMatch(*cursor, previousSearchRequest->searchPattern);
                        cursor = std::move(result->cursor);
                    }
                }
                if (!result->matchFound) message = "Pattern not found";
                else if (loop == 1) message = "search hit BOTTOM, continuing at TOP";
                else if (loop == -1) message = "search hit TOP, continuing at BOTTOM";
            } catch (...) {
                message = "No previous regular expression";
                multiplier = 0;
            }
            return std::make_unique<const VmCommandMode>(*cursor, previousCursorPosn, message);
        }
        case COMMAND_ENTER:
            return pushBackCharInTypedCommand('n');
        case INSERT: {
            const Posn previousCursorPosn = cursor->getPosn();
            cursor = editor->insertCharAt('n', *cursor);
            return defaultInsertUpdate(std::move(previousCursorPosn));
        }
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

// MARK: - ESCAPE

std::unique_ptr<const Update> VmModel::update(std::unique_ptr<const escKeyPressed> a) {
    switch (mode) {
        case COMMAND:
            multiplier = 0;
            return std::make_unique<const VmMultiplier>(0);
        case COMMAND_ENTER:
            mode = COMMAND;
            typedCommand = "";
            multiplier = 0;
            return defaultUpdate();
        case INSERT:
            mode = COMMAND;
            // CHECK FOR LINE RECORDINGS && MULTIPLIER
            cursor->moveLeftByOne();
            cursor->resetUnboundedPosn();
            return defaultUpdate();
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
                return defaultUpdate();
            }
            return std::make_unique<VmCommandEnterMode>(typedCommand);
        case INSERT: {
            const Posn previousCursorPosn = cursor->getPosn();
            if (previousCursorPosn != Posn {} && previousCursorPosn != Posn {1, 1}) {
                cursor = editor->removeCharAt(*cursor->clonePrevious());
            }
            return defaultInsertUpdate(std::move(previousCursorPosn));
        }
        case REPLACE:
            return std::make_unique<NoUpdate>();
    }
}

// MARK: - Accessors

const std::string &VmModel::getFileName() const { return fileName; }
const Editor &VmModel::getEditor() const { return *editor; }
const Cursor &VmModel::getCursor() const { return *cursor; }

// MARK: - Helpers

std::unique_ptr<const Update> VmModel::pushBackCharInTypedCommand(char c) {
    typedCommand.push_back(c);
    return std::make_unique<VmCommandEnterMode>(typedCommand);
}

std::unique_ptr<const Update> VmModel::updateForTypedCommand() {
    std::unique_ptr<const Update> update;
    try {
        update = parseColonCommand()->visit(*this);
        } catch (...) {
        try {
            update = parseForwardSlashCommand();
        } catch (...) {
            try {
                update = parseQuestionMarkCommand();
            } catch (...) {
                update = defaultUpdate();
            }
        }
    }
    mode = COMMAND;
    typedCommand.erase();
    multiplier = 0;
    return update;
}

std::unique_ptr<const VmModel::colonCommand> VmModel::parseColonCommand() const {
    if (typedCommand.empty() || typedCommand.at(0) != ':') throw parse_error {};
    
    // remove the spaces from the input
    std::string typedCommandCopy = typedCommand;
    typedCommandCopy.erase(remove_if(typedCommandCopy.begin(), typedCommandCopy.end(), isspace), typedCommandCopy.end());

    if (!typedCommandCopy.compare(":w")) return std::make_unique<const colon_w>();
    if (!typedCommandCopy.compare(":q")) return std::make_unique<const colon_q>();
    if (!typedCommandCopy.compare(":q!")) return std::make_unique<const colon_q_exclaimation_mark>();
    if (!typedCommandCopy.compare(":wq")) return std::make_unique<const colon_wq>();
    if (!typedCommandCopy.compare(":$")) return std::make_unique<const colon_dollar_sign>();
    try {
        return std::make_unique<const colon_number>(std::stoi(typedCommandCopy.substr(1, typedCommandCopy.length() - 1)));
    } catch (...) {
        return parseColonRCommand();
    }
}

std::unique_ptr<const Update> VmModel::parseForwardSlashCommand() {
    if (typedCommand.empty() || typedCommand.at(0) != '/') throw parse_error {};
    const std::string searchPattern = typedCommand.substr(1, typedCommand.length() - 1);
    std::unique_ptr<const Searchable::SearchResult> result;
    if (searchPattern.empty()) {
        try {
            result = editor->getForwardMatch(*cursor, editor->getPreviousSearch()->searchPattern);
        } catch (...) {
            return std::make_unique<const VmCommandMode>(*cursor, cursor->getPosn(), "No previous regular expression");
        }
    } else {
        result = editor->getForwardMatch(*cursor, searchPattern);
    }
    return updateForSearchPatternCommand(*result);
}

std::unique_ptr<const Update> VmModel::parseQuestionMarkCommand() {
    if (typedCommand.empty() || typedCommand.at(0) != '?') throw parse_error {};
    const std::string searchPattern = typedCommand.substr(1, typedCommand.length() - 1);
    std::unique_ptr<const Searchable::SearchResult> result;
    if (searchPattern.empty()) {
        try {
            result = editor->getBackwardMatch(*cursor, editor->getPreviousSearch()->searchPattern);
        } catch (...) {
            return std::make_unique<const VmCommandMode>(*cursor, cursor->getPosn(), "No previous regular expression");
        }
    } else result = editor->getBackwardMatch(*cursor, searchPattern);
    return updateForSearchPatternCommand(*result);
}

std::unique_ptr<const Update> VmModel::updateForSearchPatternCommand(const Searchable::SearchResult &result) {
    const Posn previousCursorPosn = cursor->getPosn();
    std::string message {};
    if (result.matchFound) {
        cursor = result.cursor->clone();
        if (result.loop == 1) message = "search hit BOTTOM, continuing at TOP";
        else if (result.loop == -1) message = "search hit TOP, continuing at BOTTOM";
    } else message = "Pattern not found";
    return std::make_unique<const VmCommandMode>(*cursor, previousCursorPosn, message);
}

std::unique_ptr<const VmModel::colon_r> VmModel::parseColonRCommand() const {
    if (typedCommand.empty() || typedCommand.length() < 2 || typedCommand.at(0) != ':') throw parse_error {};
    auto it = ++++typedCommand.begin();
    for (; it != typedCommand.end(); ++it) {
        if (!isspace(*it)) {
            if (*it == 'r') break;
            throw parse_error {};
        }
    }
    std::string fileName {};
    for (; it != typedCommand.end(); ++it) {
        if (!isspace(*it)) {
            int numOfQuotes = 0;
            for (; it != typedCommand.end() && numOfQuotes < 2; ++it) {
                if (*it == '"') ++numOfQuotes;
                fileName.push_back(*it);
            }
        }
    }
    return std::make_unique<const colon_r>(std::move(fileName));
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
        return defaultUpdate();
    }
    return std::make_unique<const VmLoadFile>(fileName, *cursor, editor->getText());
}

std::unique_ptr<const Update> VmModel::update(colon_wq c) {
    try {
        writer->write(fileName, editor->getText());
    } catch (Writer::invalidPath) {
        return defaultUpdate();
    }
    return std::make_unique<const Terminate>();
}

std::unique_ptr<const Update> VmModel::update(colon_r c) {
    if (c.fileName.empty()) {
        // DUMP OWN CONTENTS
    } else {
        try {
            reader->read(c.fileName);
        } catch (...) {
            
        }
    }
    return std::make_unique<const VmCommandMode>(*cursor, cursor->getPosn(), '"' + c.fileName + '"');
}

std::unique_ptr<const Update> VmModel::update(colon_dollar_sign c) {
    Posn previousCursorPosn = cursor->getPosn();
    cursor->setPosn(Posn {1, editor->getText().getNumOfLines()});
    cursor = editor->goToStartOfFirstWordOfLine(*cursor);
    return std::make_unique<const VmCommandMode>(*cursor, previousCursorPosn, "");
}

std::unique_ptr<const Update> VmModel::update(colon_number c) {
    Posn previousCursorPosn = cursor->getPosn();
    cursor->setPosn(Posn {1, c.ln});
    cursor = editor->goToStartOfFirstWordOfLine(*cursor);
    return std::make_unique<const VmCommandMode>(*cursor, previousCursorPosn, "");
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


VmModel::colon_r::colon_r(const std::string fileName): fileName{std::move(fileName)} {}

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

std::unique_ptr<const Update> VmModel::defaultUpdate() {
    return std::make_unique<const VmCommandMode>(*cursor, cursor->getPosn(), "");
}

std::unique_ptr<const Update> VmModel::defaultInsertUpdate(const Posn previousCursorPosn) {
    return std::make_unique<const VmInsertMode>(*cursor, std::move(previousCursorPosn));
}

std::unique_ptr<const Update> VmModel::noUpdate() {
    return std::make_unique<const NoUpdate>();
}
