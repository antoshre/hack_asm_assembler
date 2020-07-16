//
// Created by rob on 7/14/2020.
//

#ifndef HACK_TO_CPP_AST_H
#define HACK_TO_CPP_AST_H

#include <iosfwd>
#include <vector>

#include "Instruction.h"
#include "AsmFile.h"
#include "SymbolTable.h"

namespace hackasm {
    class AST {
        AsmFile assembly;
        SymbolTable symbols;

        std::vector<Instruction> listing;

    public:
        explicit AST(AsmFile);

        friend std::ostream &operator<<(std::ostream &, const AST &);
    };

}
#endif //HACK_TO_CPP_AST_H
