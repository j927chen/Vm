#include <fstream>
#include "FileWriter.h"
#include "Text.h"

void FileWriter::write(const std::string &path, const Text &text) const {
    if (path.empty()) throw invalidPath {};
    if (!isWritable(path)) throw invalidPath {};
    // MARK: - UNCOMMENT WHEN COMPILING IN STUDENT ENVIRONMENT
    /*if (!WEXITSTATUS(system(("test -r " + path).c_str()))) {
        system(("rm " + path).c_str());
    }*/
    std::ofstream f {path.c_str()};
    for (auto it = text.begin(); it->operator!=(*text.end().get()); it->operator++()) {
        f << it->operator*();
    }
}

bool FileWriter::isWritable(const std::string &path) const {
    return true;
}

FileWriter::~FileWriter() {}
