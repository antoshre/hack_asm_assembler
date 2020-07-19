#include <iostream>
#include <istream>
#include <fstream>

#include "hackasm/hackasm.h"

using namespace hackasm;

int main() {

    std::ifstream file("../../examples/Add.asm", std::ios::in);
    if (!file) {
        std::cerr << "Failed to open file.";
        return -1;
    }

    AST ast{AsmFile(file)};
    std::cout << ast << '\n';

    auto binary = ast.to_binary();
    for (const auto &line : binary) {
        std::cout << line << '\n';
    }

    return 0;
}
