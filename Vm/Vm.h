#ifndef Vm_h
#define Vm_h

#include <vector>

#include "TerminalViewController.h"
#include "Model.h"
#include "View.h"
#include "Controller.h"

class Vm {
    
    std::unique_ptr<TerminalViewController> terminalViewController;
    std::unique_ptr<Controller> controller;
    std::unique_ptr<Model> model;
    std::unique_ptr<std::vector<std::unique_ptr<View>>> views;
    
    void execute();
    
public:
    Vm();
    Vm(std::string fileName);
};

#endif
