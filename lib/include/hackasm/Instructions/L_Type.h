//
// Created by rob on 7/15/2020.
//

#ifndef HACK_TO_CPP_L_TYPE_H
#define HACK_TO_CPP_L_TYPE_H

#include "hackasm/Instructions/Symbol.h"

#include <string>
#include <iosfwd>

namespace hackasm {

    class AsmLine;

    struct L_Type {
        Symbol s;

        explicit L_Type(const AsmLine &);

        [[nodiscard]] std::string to_binary_format() const;

        static bool identify(const AsmLine &);

        friend std::ostream &operator<<(std::ostream &, const L_Type &);
    };
}
#endif //HACK_TO_CPP_L_TYPE_H
