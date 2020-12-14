#include "Searchable.h"
#include "Cursor.h"

Searchable::~Searchable() {}

Searchable::SearchRequest::SearchRequest(const std::string searchPattern, bool forward): searchPattern{std::move(searchPattern)}, forward{forward} {}

Searchable::SearchRequest::SearchRequest(const SearchRequest &other): searchPattern{other.searchPattern}, forward{other.forward} {}

Searchable::SearchResult::SearchResult(std::unique_ptr<Cursor> cursor, bool matchFound, int loop): cursor{std::move(cursor)}, matchFound{matchFound}, loop{loop} {}
