#ifndef VmTextView_h
#define VmTextView_h

#include "View.h"

class Text;
class Posn;
class ConstTextIterator;

class VmTextView: public View {
    
    int firstDisplayedRow;
    
    void display(ConstTextIterator &begin, ConstTextIterator &end);
    const Posn convertTextPosnToTerminalPosn(const Posn &p);
    
public:
    VmTextView(TerminalViewController &terminalViewController);
    void accept(const VmLoadFile &u) override;
    void accept(const VmMoveCursorDown &u) override;
    void accept(const VmMoveCursorLeft &u) override;
    void accept(const VmMoveCursorRight &u) override;
    ~VmTextView();
};



#endif 
