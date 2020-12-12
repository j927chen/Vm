#include "VmKeyboardController.h"
#include "TerminalViewController.h"
#include "Action.h"

std::map<int, std::unique_ptr<Action>> VmKeyboardController::initializeVmKeyMappings(TerminalViewController &terminalViewController) {
    std::map<int, std::unique_ptr<Action>> map;
    map[10] = std::make_unique<enterKeyPressed>();
    map[27] = std::make_unique<escKeyPressed>();
    map[58] = std::make_unique<colonKeyPressed>();
    map[104] = std::make_unique<hKeyPressed>();
    map[106] = std::make_unique<jKeyPressed>();
    map[107] = std::make_unique<kKeyPressed>();
    map[108] = std::make_unique<lKeyPressed>();
    map[terminalViewController.getBackspaceCode()] = std::make_unique<backspaceKeyPressed>();

    return map;
}

VmKeyboardController::VmKeyboardController(TerminalViewController &terminalViewController): KeyboardController{terminalViewController, initializeVmKeyMappings(terminalViewController)} {}

std::unique_ptr<const Action> VmKeyboardController::getAction() {
    int code = terminalViewController.get();
    const std::unique_ptr<Action> &action = keyMappings[code];
    if (action) return action->clone();
    return std::make_unique<otherKeyPressed>(code);
}

VmKeyboardController::~VmKeyboardController() {}
