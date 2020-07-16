//
// Created by rob on 7/15/2020.
//

#include "hackasm/Instructions/L_Type.h"
#include "hackasm/AsmLine.h"

#include "ctre.hpp"

namespace hackasm {
    bool L_Type::identify(const AsmLine &l) {
        return ctre::match<R"(\(\S+\))">(l.inst);
    }

    L_Type::L_Type(const AsmLine &l) {
        if (auto[m, v]=ctre::match<R"(\((\S+)\))">(l.inst); m) {
            Symbol _s(std::string(v.to_view()), l.inst_num, l.line_num, l.inst_num);
            this->s = _s;
        } else {
            std::runtime_error("Cannot parse L-Type: " + l.inst);
        }
    }

    std::ostream &operator<<(std::ostream &os, const L_Type &obj) {
        os << "L(" << obj.s << ")";
        return os;
    }

    std::string L_Type::to_binary_format() const {
        //L-Types are not represented in the binary format
        return "";
    }
}