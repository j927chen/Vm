#include <sys/wait.h>
#include <fstream>
#include "FileReader.h"
#include "VmText.h"

std::unique_ptr<Text> FileReader::read(const std::string &path) const {
    std::ifstream f{path.c_str()};
    f >> std::noskipws;
    std::string s;
    char c;
    while (f >> c) {
        s.push_back(c);
    }
    return std::make_unique<VmText>(s);
}

bool FileReader::isReadable(const std::string &path) const {
    return true;//!WEXITSTATUS(system(("test -r " + path).c_str()));
}
