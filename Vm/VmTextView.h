#ifndef VmTextView_h
#define VmTextView_h

#include "View.h"

class Text;
class ConstTextIterator;

class VmTextView: public View {
    
    void display(const Text &text, ConstTextIterator &constTextIterator);
    
public:
    VmTextView(TerminalViewController &terminalViewController);
    void accept(VmLoadFile &u) override;
    void accept(VmMoveCursorDown &u) override;
    void accept(VmMoveCursorLeft &u) override;
    ~VmTextView();
};



#endif 
