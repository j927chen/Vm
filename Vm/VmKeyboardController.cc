#include "VmKeyboardController.h"
#include "TerminalViewController.h"
#include "Action.h"

std::map<int, std::unique_ptr<Action>> VmKeyboardController::initializeVmKeyMappings(TerminalViewController &terminalViewController) {
    std::map<int, std::unique_ptr<Action>> map;
    map[7] = std::make_unique<control_gKeyPressed>();
    map[10] = std::make_unique<enterKeyPressed>();
    map[27] = std::make_unique<escKeyPressed>();
    map[58] = std::make_unique<colonKeyPressed>();
    map[47] = std::make_unique<forwardSlashKeyPressed>();
    map[48] = std::make_unique<numberKeyPressed>(0);
    map[49] = std::make_unique<numberKeyPressed>(1);
    map[50] = std::make_unique<numberKeyPressed>(2);
    map[51] = std::make_unique<numberKeyPressed>(3);
    map[52] = std::make_unique<numberKeyPressed>(4);
    map[53] = std::make_unique<numberKeyPressed>(5);
    map[54] = std::make_unique<numberKeyPressed>(6);
    map[55] = std::make_unique<numberKeyPressed>(7);
    map[56] = std::make_unique<numberKeyPressed>(8);
    map[57] = std::make_unique<numberKeyPressed>(9);
    map[63] = std::make_unique<questionMarkKeyPressed>();
    map[78] = std::make_unique<NKeyPressed>();
    map[94] = std::make_unique<caretKeyPressed>();
    map[104] = std::make_unique<hKeyPressed>();
    map[105] = std::make_unique<iKeyPressed>();
    map[106] = std::make_unique<jKeyPressed>();
    map[107] = std::make_unique<kKeyPressed>();
    map[108] = std::make_unique<lKeyPressed>();
    map[110] = std::make_unique<nKeyPressed>();
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
