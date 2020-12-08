#ifndef TextView_h
#define TextView_h

class Text;
class ConstTextIterator;
class TerminalViewController;

class TextView {
    
    TerminalViewController &terminalViewController;
    
public:
    TextView(TerminalViewController &terminalViewController): terminalViewController{terminalViewController} {}
    void display(const Text &text, ConstTextIterator &constTextIterator);
    ~TextView();
};

#endif
