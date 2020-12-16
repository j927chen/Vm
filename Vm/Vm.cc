#include "Vm.h"
#include "VmModel.h"
#include "Editor.h"
#include "VmKeyboardController.h"
#include "VmTextView.h"
#include "VmStatusBarView.h"
#include "ncursesViewController.h"
#include "Action.h"
#include "Update.h"

Vm::Vm(): terminalViewController{std::make_unique<ncursesViewController>()}, controller{std::make_unique<VmKeyboardController>(*terminalViewController)}, model{std::make_unique<VmModel>()}, views{std::unique_ptr<std::vector<std::unique_ptr<View>>> {new std::vector<std::unique_ptr<View>> {}}} {
    execute();
}
Vm::Vm(std::string fileName): terminalViewController{std::make_unique<ncursesViewController>()}, controller{std::make_unique<VmKeyboardController>(*terminalViewController)}, model{std::make_unique<VmModel>(std::move(fileName))}, views{std::unique_ptr<std::vector<std::unique_ptr<View>>> {new std::vector<std::unique_ptr<View>> {}}} {
    execute();
}

void Vm::execute() {
    views->push_back(std::unique_ptr<View>(new VmTextView {*terminalViewController}));
    views->push_back(std::unique_ptr<View>(new VmStatusBarView {*terminalViewController}));
    
    auto load = std::unique_ptr<VmLoadFile>(new VmLoadFile{model->getFileName(), model->getCursor(), model->getEditor().getText()});
    for (auto it = views->begin(); it != views->end(); ++it) {
        (*it)->accept(*load);
    }
    terminalViewController->moveCursorToFinalPosn();

    while (true) {
        auto b = controller->getAction()->visit(*model);
        if (dynamic_cast<const Terminate*>(b.get())) break;
        for (auto it = views->begin(); it != views->end(); ++it) {
            b->visit(**it);
        }
        terminalViewController->moveCursorToFinalPosn();
    }
}
