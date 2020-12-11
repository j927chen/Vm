#ifndef VmStatusBarView_h
#define VmStatusBarView_h

#include "View.h"

class Posn;

class VmStatusBarView: public View {
    
    void displayCursorPosn(const Posn cursorPosn);
    
public:
    VmStatusBarView(TerminalViewController &terminalViewController);
    void accept(const VmLoadFile &u) override;
    void accept(const VmMoveCursorUp &u) override;
    void accept(const VmMoveCursorDown &u) override;
    void accept(const VmMoveCursorLeft &u) override;
    void accept(const VmMoveCursorRight &u) override;
    ~VmStatusBarView();
};

#endif 
