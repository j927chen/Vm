#ifndef View_h
#define View_h

class TerminalViewController;
class VmLoadFile;
class VmMoveCursorUp;
class VmMoveCursorDown;
class VmMoveCursorLeft;
class VmMoveCursorRight;

class View {
    
protected:
    TerminalViewController &terminalViewController;
    
public:
    View(TerminalViewController &terminalViewController);
    virtual void accept(const VmLoadFile &u) = 0;
    virtual void accept(const VmMoveCursorUp &u) = 0;
    virtual void accept(const VmMoveCursorDown &u) = 0;
    virtual void accept(const VmMoveCursorLeft &u) = 0;
    virtual void accept(const VmMoveCursorRight &u) = 0;
    virtual ~View();
};

#endif 
