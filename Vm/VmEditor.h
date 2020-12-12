#ifndef VmEditor_hpp
#define VmEditor_hpp

#include "Editor.h"

class VmEditor: public Editor {
    std::unique_ptr<Text> text;
    
public:
    
    VmEditor();
    VmEditor(std::unique_ptr<Text> text);
    
    const Text &getText() const override;
    
    std::unique_ptr<Cursor> insertCharAt(char c, Cursor &cursor) override;
    std::unique_ptr<Cursor> removeCharAt(char c, Cursor &cursor) override;
    
    std::unique_ptr<Cursor> getForwardMatch(Cursor &cursor, const std::string &s) const override;
    std::unique_ptr<Cursor> getBackwardMatch(Cursor &cursor, const std::string &s) const override;
    
    ~VmEditor();
    
};

#endif
