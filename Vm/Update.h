#ifndef Update_h
#define Update_h

#include <string>
#include "Posn.h"

class View;
class Text;

class Update {
public:
    virtual void visit(View &v) const = 0;
    virtual ~Update();
};

class NoUpdate: public Update {
public:
    void visit(View &v) const override;
    ~NoUpdate();
};

class Terminate: public Update {
public:
    void visit(View &v) const override;
    ~Terminate();
};

// MARK: - Writing

class VmLoadFile: public Update {
public:
    const std::string &fileName;
    const Posn cursorPosn;
    const Text &text;
    
    VmLoadFile(const std::string &filename, const Posn cursorPosn, const Text &text);
    void visit(View &v) const override;
    ~VmLoadFile();
};

// MARK: - Cursor

class VmMoveCursor: public Update {
public:
    const Text &text;
    const Posn cursorPosn;
    const Posn previousCursorPosn;
    
    void visit(View &v) const override;
    VmMoveCursor(const Text &text, const Posn cursorPosn, const Posn previousCursorPosn);
    virtual ~VmMoveCursor();
};

class VmMoveCursorUp: public VmMoveCursor {
public:
    VmMoveCursorUp(const Text &text, const Posn cursorPosn, const Posn previousCursorPosn);
    void visit(View &v) const override;
    ~VmMoveCursorUp();
};

class VmMoveCursorDown: public VmMoveCursor {
public:
    VmMoveCursorDown(const Text &text, const Posn cursorPosn, const Posn previousCursorPosn);
    void visit(View &v) const override;
    ~VmMoveCursorDown();
};

class VmMoveCursorLeft: public VmMoveCursor {
public:
    VmMoveCursorLeft(const Text &text, const Posn cursorPosn, const Posn previousCursorPosn);
    void visit(View &v) const override;
    ~VmMoveCursorLeft();
};

class VmMoveCursorRight: public VmMoveCursor {
public:
    VmMoveCursorRight(const Text &text, const Posn cursorPosn, const Posn previousCursorPosn);
    void visit(View &v) const override;
    ~VmMoveCursorRight();
};

// MARK: - Mode

class VmCommandMode: public VmMoveCursor {
public:
    const std::string message;
    VmCommandMode(const Text &text, const Posn cursorPosn, const Posn previousCursorPosn, const std::string message);
    void visit(View &v) const override;
    ~VmCommandMode();
};

class VmCommandEnterMode: public Update {
public:
    const std::string &typedCommand;
    VmCommandEnterMode(const std::string &typedCommand);
    void visit(View &v) const override;
    ~VmCommandEnterMode();
};


#endif 
