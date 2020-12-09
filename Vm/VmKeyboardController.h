#ifndef VmKeyboardController_h
#define VmKeyboardController_h

#include "KeyboardController.h"

class VmKeyboardController: public KeyboardController {
    
public:
    VmKeyboardController(TerminalViewController &terminalViewController);
    const Action &getAction() override;
    ~VmKeyboardController();
};

#endif
