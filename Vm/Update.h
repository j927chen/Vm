#ifndef Update_h
#define Update_h

#include <string>
#include "Posn.h"

class View;
class Text;
class Cursor;

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
    const Cursor &cursor;
    const Text &text;
    
    VmLoadFile(const std::string &filename, const Cursor &cursor, const Text &text);
    void visit(View &v) const override;
    ~VmLoadFile();
};

// MARK: - Cursor

class VmMoveCursor: public Update {
public:
    const Cursor &cursor;
    const Posn previousCursorPosn;
    
    void visit(View &v) const override;
    VmMoveCursor(const Cursor &cursor, const Posn previousCursorPosn);
    virtual ~VmMoveCursor();
};

class VmMoveCursorUp: public VmMoveCursor {
public:
    VmMoveCursorUp(const Cursor &cursor, const Posn previousCursorPosn);
    void visit(View &v) const override;
    ~VmMoveCursorUp();
};

class VmMoveCursorDown: public VmMoveCursor {
public:
    VmMoveCursorDown(const Cursor &cursor, const Posn previousCursorPosn);
    void visit(View &v) const override;
    ~VmMoveCursorDown();
};

class VmMoveCursorLeft: public VmMoveCursor {
public:
    VmMoveCursorLeft(const Cursor &cursor, const Posn previousCursorPosn);
    void visit(View &v) const override;
    ~VmMoveCursorLeft();
};

class VmMoveCursorRight: public VmMoveCursor {
public:
    VmMoveCursorRight(const Cursor &cursor, const Posn previousCursorPosn);
    void visit(View &v) const override;
    ~VmMoveCursorRight();
};

// MARK: - Mode

class VmCommandMode: public VmMoveCursor {
public:
    const std::string message;
    VmCommandMode(const Cursor &cursor, const Posn previousCursorPosn, const std::string message);
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

class VmInsertMode: public VmMoveCursor {
public:
    VmInsertMode(const Cursor &cursor, const Posn previousCursorPosn);
    void visit(View &v) const override;
    ~VmInsertMode();
};

class VmMultiplier: public Update {
public:
    int multiplier;
    VmMultiplier(int multiplier);
    void visit(View &v) const override;
    ~VmMultiplier();
};



#endif 
