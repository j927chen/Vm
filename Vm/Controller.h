#ifndef Controller_h
#define Controller_h

#include <memory>

class TerminalViewController;
class Action;

class Controller {
protected:
    TerminalViewController &terminalViewController;
public:
    Controller(TerminalViewController &terminalViewController);
    virtual std::unique_ptr<const Action> getAction() = 0;
    virtual ~Controller();
};

#endif 
