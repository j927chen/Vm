#ifndef View_h
#define View_h

class TerminalViewController;
class NoUpdate;
class VmLoadFile;
class VmCommandMode;
class VmCommandEnterMode;
class VmInsertMode;
class VmMoveCursor;
class VmMoveCursorUp;
class VmMoveCursorDown;
class VmMoveCursorLeft;
class VmMoveCursorRight;

class View {
    
protected:
    TerminalViewController &terminalViewController;
    
public:
    View(TerminalViewController &terminalViewController);
    virtual void accept(const NoUpdate &u) = 0;
    virtual void accept(const VmLoadFile &u) = 0;
    virtual void accept(const VmCommandMode &u) = 0;
    virtual void accept(const VmCommandEnterMode &u) = 0;
    virtual void accept(const VmInsertMode &u) = 0;
    virtual void accept(const VmMoveCursor &u) = 0;
    virtual void accept(const VmMoveCursorUp &u) = 0;
    virtual void accept(const VmMoveCursorDown &u) = 0;
    virtual void accept(const VmMoveCursorLeft &u) = 0;
    virtual void accept(const VmMoveCursorRight &u) = 0;
    virtual ~View();
};

#endif 
