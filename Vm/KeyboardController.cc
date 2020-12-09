#include "KeyboardController.h"
#include "Action.h"

KeyboardController::KeyboardController(TerminalViewController &terminalViewController, std::map<int, std::unique_ptr<Action>> keyMappings): Controller{terminalViewController}, keyMappings{std::move(keyMappings)} {}

KeyboardController::~KeyboardController() {}
