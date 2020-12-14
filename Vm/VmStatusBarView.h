#ifndef VmStatusBarView_h
#define VmStatusBarView_h

#include "View.h"

class Posn;

class VmStatusBarView: public View {
    
    const std::string standardZeroCursorColReplacement = "0-1";
    
    int terminalXCursorPosn;
    int terminalYTop;
    void displayCursorPosn(const Posn &cursorPosn);
    void displayCursorPosn(const Posn &cursorPosn, const std::string &colReplacement);
    
public:
    VmStatusBarView(TerminalViewController &terminalViewController);
    void accept(const NoUpdate &u) override;
    void accept(const VmLoadFile &u) override;
    void accept(const VmCommandMode &u) override;
    void accept(const VmCommandEnterMode &u) override;
    void accept(const VmInsertMode &u) override;
    void accept(const VmMoveCursor &u) override;
    void accept(const VmMoveCursorUp &u) override;
    void accept(const VmMoveCursorDown &u) override;
    void accept(const VmMoveCursorLeft &u) override;
    void accept(const VmMoveCursorRight &u) override;
    ~VmStatusBarView();
};

#endif 
