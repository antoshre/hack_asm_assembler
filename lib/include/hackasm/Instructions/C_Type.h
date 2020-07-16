//
// Created by rob on 7/15/2020.
//

#ifndef HACK_TO_CPP_C_TYPE_H
#define HACK_TO_CPP_C_TYPE_H

#include "hackasm/Instructions/Symbol.h"

#include <string>
#include <iosfwd>


namespace hackasm {

    class AsmLine;

    struct C_Type {
        std::string dest_mnemonic;
        std::string comp_mnemonic;
        std::string jump_mnemonic;

        explicit C_Type(const AsmLine &);

        [[nodiscard]] std::string to_binary_format() const;

        static bool identify(const AsmLine &);

        friend std::ostream &operator<<(std::ostream &, const C_Type &);
    };
}
#endif //HACK_TO_CPP_C_TYPE_H
