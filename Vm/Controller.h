#ifndef Controller_h
#define Controller_h

class TerminalViewController;
class Action;

class Controller {
protected:
    TerminalViewController &terminalViewController;
public:
    Controller(TerminalViewController &terminalViewController);
    virtual const Action &getAction() = 0;
    virtual ~Controller();
};

#endif 
