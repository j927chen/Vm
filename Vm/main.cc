#include <string>
#include "Vm.h"

int main(int argc, const char * argv[]) {
    if (argc == 1) {
        Vm vm {};
    }
    else {
        Vm vm {argv[1]};
    }
}
