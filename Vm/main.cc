#include <iostream>
#include <memory>
#include "FileReader.h"
#include "FileWriter.h"
#include "VmText.h"
#include "ncursesViewController.h"
#include "TextView.h"
#include "Posn.h"

int main(int argc, const char * argv[]) {
    const std::string fileName = argv[1];
    std::unique_ptr<TerminalViewController> terminalViewController {new ncursesViewController {}};
    const std::unique_ptr<Reader> reader {new FileReader};
    const std::unique_ptr<Writer> writer {new FileWriter};
    std::unique_ptr<Text> text = reader->read(fileName);
    std::unique_ptr<TextView> textView {new TextView {*terminalViewController.get()}};
    auto it = text->cbegin();
    textView->display(*text.get(), *it);
    //writer->write(fileName, *text.get());
}
