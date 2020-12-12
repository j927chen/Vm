#ifndef VmTextView_h
#define VmTextView_h

#include "View.h"

class Text;
class Posn;
class ConstTextIterator;

class VmTextView: public View {
    
    int firstDisplayedTextRowNum;
    int maxWidth;
    int maxHeight;
    bool displaysEndOfText;
    
    void moveCursor(int textColumnNum, int relativeTextViewRowNum);
    void display(ConstTextIterator &begin, ConstTextIterator &end);
    const Posn convertTextPosnToTerminalPosn(const Posn p);
    int getMaxRelativeTextViewRowNum(int textLineNum, const Text &text) const;
    int getMinRelativeTextViewRowNum(int textLineNum, const Text &text) const;
    
    
public:
    VmTextView(TerminalViewController &terminalViewController);
    void accept(const NoUpdate &u) override;
    void accept(const VmLoadFile &u) override;
    void accept(const VmCommandMode &u) override;
    void accept(const VmCommandEnterMode &u) override;
    void accept(const VmMoveCursorUp &u) override;
    void accept(const VmMoveCursorDown &u) override;
    void accept(const VmMoveCursorLeft &u) override;
    void accept(const VmMoveCursorRight &u) override;
    ~VmTextView();
};



#endif 
