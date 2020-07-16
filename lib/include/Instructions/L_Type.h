//
// Created by rob on 7/15/2020.
//

#ifndef HACK_TO_CPP_L_TYPE_H
#define HACK_TO_CPP_L_TYPE_H

#include "Instructions/Symbol.h"

#include <iosfwd>

namespace hackasm {

    class AsmLine;

    struct L_Type {
        Symbol s;

        explicit L_Type(const AsmLine &);

        static bool identify(const AsmLine &);

        friend std::ostream &operator<<(std::ostream &, const L_Type &);
    };
}
#endif //HACK_TO_CPP_L_TYPE_H
