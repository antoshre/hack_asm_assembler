//
// Created by rob on 7/15/2020.
//

#include "Instructions/A_Type.h"
#include "AsmLine.h"
#include "AsmLine.h"
#include "ctre.hpp"

namespace hackasm {

    A_Type::A_Type(const AsmLine &l) {
        //Match "@<non-whitespace>"
        if (auto[m, v]=ctre::match<R"(@(\S+))">(l.inst); m) {
            Symbol _s(std::string(v.to_view()), l.line_num, l.inst_num);
            this->s = _s;
        } else {
            throw std::runtime_error("Cannot parse A-Type: " + l.inst);
        }
    }

    //Match "@<non-whitespace>"
    bool A_Type::identify(const AsmLine &l) {
        return ctre::match<R"(@\S+)">(l.inst);
    }

    std::ostream &operator<<(std::ostream &os, const A_Type &obj) {
        os << "A(" << obj.s << ")";
        return os;
    }
}