#ifndef Searchable_hpp
#define Searchable_hpp

#include <memory>

class Cursor;

class Searchable {
    
    
public:
    virtual std::unique_ptr<Cursor> getForwardMatch(const Cursor &cursor, const std::string &s) const = 0;
    virtual std::unique_ptr<Cursor> getBackwardMatch(const Cursor &cursor, const std::string &s) const = 0;
    virtual std::unique_ptr<Cursor> goToStartOfFirstWordOfLine(const Cursor &cursor) const = 0;
    virtual ~Searchable();
};

#endif
