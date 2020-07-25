//
// Created by rob on 7/22/20.
//

#ifndef HACK_ASM_ASSEMBLER_B_TYPE_H
#define HACK_ASM_ASSEMBLER_B_TYPE_H

#include <string>
#include <string_view>
#include <iosfwd>


namespace hackasm {

    class AsmLine;
    class SymbolTable;

    struct B_Type {
        std::string_view comp_mnemonic;
        std::string_view jump_mnemonic;
        int line_loc; //line location in original source, zero-indexed
        int inst_loc; //location in the instruction stream, zero-indexed

        explicit B_Type(const AsmLine &);

        [[nodiscard]] std::string to_string() const;
        [[nodiscard]] std::string to_string(const SymbolTable&) const;
        [[nodiscard]] std::string to_binary_format(const SymbolTable&) const;

        static bool identify(const AsmLine &);

        friend std::ostream &operator<<(std::ostream &, const B_Type &);
    };
}

#endif //HACK_ASM_ASSEMBLER_B_TYPE_H
