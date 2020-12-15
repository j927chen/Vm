#include "VmEditor.h"
#include "VmText.h"
#include "VmCursor.h"

VmEditor::VmEditor(): text{std::make_unique<VmText>()}, previousSearch{std::unique_ptr<const SearchRequest> {}} {}

VmEditor::VmEditor(std::unique_ptr<Text> text): text{std::move(text)}, previousSearch{std::unique_ptr<const SearchRequest> {}} {}

const Text &VmEditor::getText() const { return *text; }

// MARK: - Editable

std::unique_ptr<Cursor> VmEditor::insertCharAt(char c, const Cursor &cursor) {
    return std::make_unique<VmCursor>(*text, *text->insert(c, cursor.getIt())->next());
}

std::unique_ptr<Cursor> VmEditor::removeCharAt(const Cursor &cursor) {
    return std::make_unique<VmCursor>(*text, *text->remove(cursor.getIt()));
}


// MARK: - Searchable

std::unique_ptr<const Editor::SearchRequest> VmEditor::getPreviousSearch() const {
    if (previousSearch == nullptr) throw no_search_history {};
    return std::make_unique<const SearchRequest>(*previousSearch);
}

std::unique_ptr<Searchable::SearchResult> VmEditor::getForwardMatch(const Cursor &cursor, const std::string &searchPattern) {
    
    previousSearch = std::make_unique<const SearchRequest>(searchPattern, true);
    
    if (searchPattern.empty()) return std::make_unique<SearchResult>(cursor.clone(), true, 0);
    if (cursor.getPosn() == Posn {}) {
        return std::make_unique<SearchResult>(cursor.clone(), false, 0);
    }
    
    auto &text = cursor.getText();
    auto end = text.end();
    
    for (auto it = cursor.getIt().clone()->operator++(); it->operator!=(*end); it->operator++()) {
        if (matches(searchPattern, *it, *end)) {
            return std::make_unique<SearchResult>(std::make_unique<VmCursor>(text, *it), true, 0);
        }
    }
    
    auto nextIt = cursor.getIt().next();
    
    for (auto it = text.begin(); it->operator!=(*nextIt); it->operator++()) {
        if (matches(searchPattern, *it, *end)) return std::make_unique<SearchResult>(std::make_unique<VmCursor>(text, *it), true, 1);
    }
    
    return std::make_unique<SearchResult>(std::make_unique<VmCursor>(text, cursor.getIt()), false, 1);
}

std::unique_ptr<Searchable::SearchResult> VmEditor::getBackwardMatch(const Cursor &cursor, const std::string &searchPattern) {
    
    previousSearch = std::make_unique<const SearchRequest>(searchPattern, false);
    
    if (searchPattern.empty()) return std::make_unique<SearchResult>(cursor.clone(), true, 0);
    if (cursor.getPosn() == Posn {}) {
        return std::make_unique<SearchResult>(cursor.clone(), false, 0);
    }
    
    auto &text = cursor.getText();
    auto begin = text.begin();
    auto end = text.end();
    
    if (cursor.getIt() != *begin) {
        for (auto it = cursor.getIt().clone()->operator--();; it->operator--()) {
            if (matches(searchPattern, *it, *end)) {
                return std::make_unique<SearchResult>(std::make_unique<VmCursor>(text, *it), true, 0);
            }
            if (it->operator==(*begin)) break;
        }
    }
    
    auto previousIt = cursor.getIt().previous();
    
    for (auto it = end->operator--(); it->operator!=(*previousIt); it->operator--()) {
        if (matches(searchPattern, *it, *end)) return std::make_unique<SearchResult>(std::make_unique<VmCursor>(text, *it), true, -1);
    }
    
    return std::make_unique<SearchResult>(std::make_unique<VmCursor>(text, cursor.getIt()), false, -1);
}

std::unique_ptr<Cursor> VmEditor::goToStartOfLine(const Cursor &cursor) const {
    auto newCursor = cursor.clone();
    newCursor->setPosn(Posn {1, cursor.getPosn().y});
    return newCursor;
}

std::unique_ptr<Cursor> VmEditor::goToStartOfFirstWordOfLine(const Cursor &cursor) const {
    auto newCursor = cursor.clone();
    if (newCursor->getPosn() != Posn {} && newCursor->get() != '\n') {
        for (; isspace(newCursor->get()) && newCursor->getNext() != '\n'; newCursor->moveRightByOne()) {}
    }
    return newCursor;
}

std::unique_ptr<Cursor> VmEditor::goToEndOfLineNoNewLine(const Cursor &cursor) const {
    auto newCursor = cursor.clone();
    if (newCursor->getPosn() != Posn {}) {
        while (newCursor->get() != '\n' && newCursor->getNext() != '\n') {
            newCursor->moveRightByOneNoNewLine();
        }
    }
    return newCursor;
}

bool VmEditor::matches(const std::string &searchPattern, const ConstTextIterator &begin, const ConstTextIterator &end) const {
    auto beginIt = begin.clone();
    for (auto patternIt = searchPattern.begin(); patternIt != searchPattern.end(); ++patternIt) {
        if (beginIt->operator==(end) || *patternIt != beginIt->operator*()) return false;
        beginIt->operator++();
    }
    return true;
}

VmEditor::~VmEditor() {}
