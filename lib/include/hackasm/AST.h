//
// Created by rob on 7/14/2020.
//

#ifndef HACK_TO_CPP_AST_H
#define HACK_TO_CPP_AST_H

#include <iosfwd>
#include <vector>

#include "hackasm/Instruction.h"
#include "hackasm/AsmFile.h"
#include "hackasm/SymbolTable.h"

namespace hackasm {
    struct AST {
        AsmFile assembly;
        SymbolTable symbols;

        std::vector<Instruction> listing;

    public:
        //explicit AST(AsmFile);
        explicit AST(std::istream&);

        [[nodiscard]] const AsmFile &get_asmfile() const;

        [[nodiscard]] const SymbolTable &get_symbol_table() const;

        [[nodiscard]] const std::vector<Instruction> &get_listing() const;

        [[nodiscard]] std::vector<std::string> to_binary() const;

        friend std::ostream &operator<<(std::ostream &, const AST &);
    };

}
#endif //HACK_TO_CPP_AST_H
