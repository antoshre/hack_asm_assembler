#include <iostream>
#include <istream>
#include <fstream>

#include "AsmFile.h"
#include "AST.h"

using namespace hackasm;

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cout << "Usage: disassembler.exe [filename.asm]\n";
        return -1;
    }

    std::ifstream file(argv[1], std::ios::in);

    AST ast{AsmFile(file)};
    std::cout << ast;

    return 0;
}
