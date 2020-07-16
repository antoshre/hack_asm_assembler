#include <iostream>
#include <istream>
#include <fstream>

#include "hackasm\AsmFile.h"
#include "hackasm\AST.h"

using namespace hackasm;

int main() {

    std::ifstream file("../../examples/Add.asm", std::ios::in);
    if (!file) {
        std::cerr << "Failed to open file.";
        return -1;
    }

    AST ast{AsmFile(file)};
    std::cout << ast;

    return 0;
}
