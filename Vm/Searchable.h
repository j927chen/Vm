#ifndef Searchable_hpp
#define Searchable_hpp

#include <memory>

class Cursor;

class Searchable {
    
    
public:
    virtual std::unique_ptr<Cursor> getForwardMatch(Cursor &cursor, const std::string &s) const = 0;
    virtual std::unique_ptr<Cursor> getBackwardMatch(Cursor &cursor, const std::string &s) const = 0;
    virtual ~Searchable();
};

#endif
