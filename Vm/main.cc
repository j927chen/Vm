#include <iostream>
#include <memory>
#include "FileReader.h"
#include "FileWriter.h"
#include "VmText.h"
#include "ncursesViewController.h"
#include "VmTextView.h"
#include "VmKeyboardController.h"
#include "VmModel.h"
#include "Action.h"
#include "Update.h"
#include "Posn.h"

int main(int argc, const char * argv[]) {
    const std::string fileName = argv[1];
    std::unique_ptr<TerminalViewController> terminalViewController {new ncursesViewController {}};
    std::unique_ptr<View> view {new VmTextView {*terminalViewController.get()}};
    std::unique_ptr<Controller> controller {new VmKeyboardController{*terminalViewController}};
    
    std::unique_ptr<Reader> reader {new FileReader};
    std::unique_ptr<Writer> writer {new FileWriter};
    std::unique_ptr<Text> text = reader->read(fileName);
    std::unique_ptr<Model> model {new VmModel{std::move(text), std::move(reader), std::move(writer)}};
    
    view->accept(*std::unique_ptr<VmLoadFile>(new VmLoadFile{fileName, model->getText()}).get());
    while (!dynamic_cast<const escKeyPressed*>(&controller->getAction())) {
        
    }
    //writer->write(fileName, *text.get());
}
