#include "VmKeyboardController.h"
#include "TerminalViewController.h"
#include "Action.h"

std::map<int, std::unique_ptr<Action>> initializeVmKeyMappings() {
    std::map<int, std::unique_ptr<Action>> map;
    map[-1] = std::make_unique<unknownKeyPressed>();
    map[104] = std::make_unique<hKeyPressed>();
    map[27] = std::make_unique<escKeyPressed>();

    return map;
}

VmKeyboardController::VmKeyboardController(TerminalViewController &terminalViewController): KeyboardController{terminalViewController, initializeVmKeyMappings()} {}

const Action &VmKeyboardController::getAction() {
    const std::unique_ptr<Action> &action = keyMappings[terminalViewController.get()];
    return action ? *action.get() : *keyMappings[-1].get();
}

VmKeyboardController::~VmKeyboardController() {}
