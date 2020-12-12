#ifndef Editor_h
#define Editor_h

#include "Editable.h"
#include "Searchable.h"

class Text;

class Editor: public Editable, public Searchable {
    
public:
    virtual const Text &getText() const = 0;
    virtual ~Editor();
};

#endif
