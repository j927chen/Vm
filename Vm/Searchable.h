#ifndef Searchable_hpp
#define Searchable_hpp

#include <string>
#include <memory>

class Cursor;

class Searchable {
    
public:
    
    class SearchRequest {
    public:
        const std::string searchPattern;
        bool forward;
        SearchRequest(const std::string searchPattern, bool forward);
        SearchRequest(const SearchRequest &other);
    };
    
    class SearchResult {
    public:
        SearchResult(std::unique_ptr<Cursor> cursor, bool matchFound, int loop);
        std::unique_ptr<Cursor> cursor;
        bool matchFound;
        int loop;
    };

    class no_search_history {};
    
    virtual std::unique_ptr<const SearchRequest> getPreviousSearch() const = 0;
    virtual std::unique_ptr<SearchResult> getForwardMatch(const Cursor &cursor, const std::string &searchPattern) = 0;
    virtual std::unique_ptr<SearchResult> getBackwardMatch(const Cursor &cursor, const std::string &searchPattern) = 0;
    virtual std::unique_ptr<Cursor> goToStartOfFirstWordOfLine(const Cursor &cursor) const = 0;
    virtual ~Searchable();
};

#endif
