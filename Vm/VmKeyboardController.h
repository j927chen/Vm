#ifndef VmKeyboardController_h
#define VmKeyboardController_h

#include "KeyboardController.h"

class VmKeyboardController: public KeyboardController {
    
    std::map<int, std::unique_ptr<Action>> initializeVmKeyMappings(TerminalViewController &terminalViewController);
    
public:
    VmKeyboardController(TerminalViewController &terminalViewController);
    std::unique_ptr<const Action> getAction() override;
    ~VmKeyboardController();
};

#endif
