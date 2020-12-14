#ifndef VmEditor_hpp
#define VmEditor_hpp

#include "Editor.h"

class ConstTextIterator;

class VmEditor: public Editor {
    
    std::unique_ptr<Text> text;
    std::unique_ptr<const SearchRequest> previousSearch;
    
    bool matches(const std::string &searchPattern, const ConstTextIterator &begin, const ConstTextIterator &end) const;
    
public:
    
    VmEditor();
    VmEditor(std::unique_ptr<Text> text);
    
    const Text &getText() const override;
    
    std::unique_ptr<Cursor> insertCharAt(char c, const Cursor &cursor) override;
    std::unique_ptr<Cursor> removeCharAt(const Cursor &cursor) override;
    
    std::unique_ptr<const SearchRequest> getPreviousSearch() const override;
    std::unique_ptr<SearchResult> getForwardMatch(const Cursor &cursor, const std::string &searchPattern) override;
    std::unique_ptr<SearchResult> getBackwardMatch(const Cursor &cursor, const std::string &searchPattern) override;
    
    std::unique_ptr<Cursor> goToStartOfFirstWordOfLine(const Cursor &cursor) const override;
    
    ~VmEditor();
    
};

#endif
