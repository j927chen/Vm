#ifndef Update_h
#define Update_h

class View;
class Text;

class Update {
public:
    virtual void visit(View &v) = 0;
    virtual ~Update();
};

class ConstTextIterator;

class VmLoadFile: public Update {
public:
    const std::string &fileName;
    const Text &text;
    
    VmLoadFile(const std::string &filename, const Text &text);
    void visit(View &v) override;
    ~VmLoadFile();
};

class VmMoveCursor: public Update {
public:
    const Text &text;
    ConstTextIterator &constTextIterator;
    
    VmMoveCursor(const Text &text, ConstTextIterator &constTextIterator);
    virtual ~VmMoveCursor();
};

class VmMoveCursorDown: public VmMoveCursor {
public:
    VmMoveCursorDown(const Text &text, ConstTextIterator &constTextIterator);
    void visit(View &v) override;
    ~VmMoveCursorDown();
};

class VmMoveCursorLeft: public VmMoveCursor {
public:
    VmMoveCursorLeft(const Text &text, ConstTextIterator &constTextIterator);
    void visit(View &v) override;
    ~VmMoveCursorLeft();
};

#endif 
