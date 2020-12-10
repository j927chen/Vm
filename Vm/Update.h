#ifndef Update_h
#define Update_h

#include "Posn.h"

class View;
class Text;

class Update {
public:
    virtual void visit(View &v) const = 0;
    virtual ~Update();
};

class VmLoadFile: public Update {
public:
    const std::string &fileName;
    const Text &text;
    
    VmLoadFile(const std::string &filename, const Text &text);
    void visit(View &v) const override;
    ~VmLoadFile();
};


class VmMoveCursor: public Update {
public:
    const Text &text;
    const Posn cursorPosn;
    
    VmMoveCursor(const Text &text, const Posn cursorPosn);
    virtual ~VmMoveCursor();
};

class VmMoveCursorDown: public VmMoveCursor {
public:
    VmMoveCursorDown(const Text &text, const Posn cursorPosn);
    void visit(View &v) const override;
    ~VmMoveCursorDown();
};

class VmMoveCursorLeft: public VmMoveCursor {
public:
    VmMoveCursorLeft(const Text &text, const Posn cursorPosn);
    void visit(View &v) const override;
    ~VmMoveCursorLeft();
};

class VmMoveCursorRight: public VmMoveCursor {
public:
    VmMoveCursorRight(const Text &text, const Posn cursorPosn);
    void visit(View &v) const override;
    ~VmMoveCursorRight();
};

#endif 
