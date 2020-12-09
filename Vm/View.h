#ifndef View_h
#define View_h

class TerminalViewController;
class VmLoadFile;
class VmMoveCursorDown;
class VmMoveCursorLeft;

class View {
    
protected:
    TerminalViewController &terminalViewController;
    
public:
    View(TerminalViewController &terminalViewController);
    virtual void accept(VmLoadFile &u) = 0;
    virtual void accept(VmMoveCursorDown &u) = 0;
    virtual void accept(VmMoveCursorLeft &u) = 0;
    virtual ~View();
};

#endif 
