#ifndef KeyboardController_h
#define KeyboardController_h

#include <map>
#include "Controller.h"

class KeyboardController: public Controller {
    
protected:
    std::map<int, std::unique_ptr<Action>> keyMappings;
    
public:
    KeyboardController(TerminalViewController &terminalViewController, std::map<int, std::unique_ptr<Action>> keyMappings);
    virtual ~KeyboardController();
};

#endif
