//
// Created by rob on 7/15/2020.
//

#ifndef HACK_TO_CPP_C_TYPE_H
#define HACK_TO_CPP_C_TYPE_H

#include "Instructions/Symbol.h"

#include <iosfwd>


namespace hackasm {

    class AsmLine;

    struct C_Type {
        std::string dest_mnemonic;
        std::string comp_mnemonic;
        std::string jump_mnemonic;

        explicit C_Type(const AsmLine &);

        static bool identify(const AsmLine &);

        friend std::ostream &operator<<(std::ostream &, const C_Type &);
    };
}
#endif //HACK_TO_CPP_C_TYPE_H
