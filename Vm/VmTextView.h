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
    
    void moveCursor(int textColumnNum, int relativeTextViewRowNum);
    int checkEndOfDisplay(const ConstTextIterator &itAtBeginningOfFirstDisplayedTextRow, const ConstTextIterator &end);
    void display(ConstTextIterator &begin, ConstTextIterator &end);
    int getMaxRelativeTextViewRowNum(int textLineNum, const ConstTextIterator &itAtBeginningOfFirstDisplayedTextRow) const;
    int getMinRelativeTextViewRowNum(int textLineNum, const ConstTextIterator &itAtBeginningOfFirstDisplayedTextRow) const;
    int getNumOfTextViewRowsForTextLine(const ConstTextIterator &itAtBeginningOfTextLine) const;
    const Posn convertTextPosnToTerminalPosn(const Posn p);
    
    
public:
    VmTextView(TerminalViewController &terminalViewController);
    void accept(const NoUpdate &u) override;
    void accept(const VmLoadFile &u) override;
    void accept(const VmCommandMode &u) override;
    void accept(const VmCommandEnterMode &u) override;
    void accept(const VmInsertMode &u) override;
    void accept(const VmMultiplier &u) override;
    void accept(const VmMoveCursor &u) override;
    void accept(const VmMoveCursorUp &u) override;
    void accept(const VmMoveCursorDown &u) override;
    void accept(const VmMoveCursorLeft &u) override;
    void accept(const VmMoveCursorRight &u) override;
    ~VmTextView();
};



#endif 
