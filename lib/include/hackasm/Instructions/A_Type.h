//
// Created by rob on 7/15/2020.
//

#ifndef HACK_TO_CPP_A_TYPE_H
#define HACK_TO_CPP_A_TYPE_H

#include "hackasm/Instructions/Symbol.h"

#include <string>
#include <iosfwd>


namespace hackasm {

    class AsmLine;

    /*
     * A-Type instructions are always of the form:
     * "@<value>"
     * The value can be an integer constant or a symbol
     */
    struct A_Type {

        Symbol s;

        //Construct an A-Type from the given line
        explicit A_Type(const AsmLine &);

        [[nodiscard]] std::string to_binary_format() const;

        //Identify if the given line contains an A-Type
        //Does NOT verify if the symbol is valid
        static bool identify(const AsmLine &);

        //Pretty-print the instruction
        friend std::ostream &operator<<(std::ostream &, const A_Type &);
    };
}
#endif //HACK_TO_CPP_A_TYPE_H
