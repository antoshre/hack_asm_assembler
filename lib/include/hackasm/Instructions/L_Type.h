//
// Created by rob on 7/15/2020.
//

#ifndef HACK_TO_CPP_L_TYPE_H
#define HACK_TO_CPP_L_TYPE_H

#include <string>
#include <string_view>
#include <iosfwd>

namespace hackasm {

    class AsmLine;
    class SymbolTable;

    struct L_Type {
        std::string_view label;
        int line_loc; //line location in original source, zero-indexed
        int inst_loc; //location in the instruction stream, zero-indexed

        explicit L_Type(const AsmLine &);

        [[nodiscard]] std::string to_string() const;
        [[nodiscard]] std::string to_string(const SymbolTable&) const;
        [[nodiscard]] std::string to_binary_format(const SymbolTable&) const;

        static bool identify(const AsmLine &);

        friend std::ostream &operator<<(std::ostream &, const L_Type &);
    };
}
#endif //HACK_TO_CPP_L_TYPE_H
