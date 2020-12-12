#include <iostream>
#include <memory>
#include "FileReader.h"
#include "FileWriter.h"
#include "VmText.h"
#include "Cursor.h"
#include "ncursesViewController.h"
#include "VmTextView.h"
#include "VmStatusBarView.h"
#include "VmKeyboardController.h"
#include "VmModel.h"
#include "VmEditor.h"
#include "Action.h"
#include "Update.h"
#include "Posn.h"

int main(int argc, const char * argv[]) {

    std::unique_ptr<TerminalViewController> terminalViewController {new ncursesViewController {}};
    std::unique_ptr<View> textView {new VmTextView {*terminalViewController}};
    std::unique_ptr<View> statusView {new VmStatusBarView {*terminalViewController}};
    std::unique_ptr<Controller> controller {new VmKeyboardController{*terminalViewController}};
    
    std::unique_ptr<Model> model {argc == 1 ? new VmModel {} : new VmModel {argv[1]}};
    
    auto load = std::unique_ptr<VmLoadFile>(new VmLoadFile{model->getFileName(), model->getCursor().getPosn(), model->getEditor().getText()});
    textView->accept(*load);
    statusView->accept(*load);
    terminalViewController->moveCursorToFinalPosn();

    while (true) {
        auto b = controller->getAction()->visit(*model);
        if (dynamic_cast<const Terminate*>(b.get())) break;
        b->visit(*textView);
        b->visit(*statusView);
        terminalViewController->moveCursorToFinalPosn();
    }
}
