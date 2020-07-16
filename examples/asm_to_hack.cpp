//
// Created by rob on 7/16/2020.
//

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
    auto output = ast.to_binary();
    std::ofstream outfile("Add.hack", std::ios::out);
    for (const auto &line : output) {
        outfile << line << '\n';
    }

    std::ofstream listfile("Add.list", std::ios::out);
    listfile << ast;

    return 0;
}
