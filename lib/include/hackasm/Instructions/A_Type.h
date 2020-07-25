//
// Created by rob on 7/15/2020.
//

#ifndef HACK_TO_CPP_A_TYPE_H
#define HACK_TO_CPP_A_TYPE_H

#include <string>
#include <string_view>
#include <iosfwd>


namespace hackasm {

    class AsmLine;
    class SymbolTable;

    /*
     * A-Type instructions are always of the form:
     * "@<value>"
     */
    struct A_Type {

        std::string_view value;

        int line_loc; //line location in original source, zero-indexed
        int inst_loc; //location in the instruction stream, zero-indexed

        //Construct an A-Type from the given line
        explicit A_Type(const AsmLine &);

        [[nodiscard]] std::string to_string() const;
        [[nodiscard]] std::string to_string(const SymbolTable&) const;
        [[nodiscard]] std::string to_binary_format(const SymbolTable&) const;

        //Identify if the given line contains an A-Type
        //Does NOT verify if the symbol is valid
        static bool identify(const AsmLine &);

        //Pretty-print the instruction
        friend std::ostream &operator<<(std::ostream &, const A_Type &);
    };
}
#endif //HACK_TO_CPP_A_TYPE_H
