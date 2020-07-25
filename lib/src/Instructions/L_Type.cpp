//
// Created by rob on 7/15/2020.
//

#include "hackasm/Instructions/L_Type.h"
#include "hackasm/AsmLine.h"
#include "hackasm/SymbolTable.h"
#include <stdexcept>
#include <string>

#include "ctre.hpp"

namespace hackasm {
    bool L_Type::identify(const AsmLine &l) {
        return ctre::match<R"(\(\S+\))">(l.inst);
    }

    L_Type::L_Type(const AsmLine &l) {
        if (auto[m, v]=ctre::match<R"(\((\S+)\))">(l.inst); m) {
            label = v.to_view();
            line_loc = l.line_num;
            inst_loc = l.inst_num;
        } else {
            std::runtime_error("Cannot parse L-Type: " + l.inst);
        }
    }

    std::ostream &operator<<(std::ostream &os, const L_Type &obj) {
        //os << "L(" << obj.label << ")";
        return os;
    }

    std::string L_Type::to_binary_format(const SymbolTable&) const {
        //L-Types are not represented in the binary format
        return "";
    }

    std::string L_Type::to_string() const {
        return "L(" + std::string(label) + ")";
    }

    std::string L_Type::to_string(const SymbolTable &syms) const {
        return "L(" + std::string(label) + " -> " + std::to_string(syms[label]) + ")";
    }
}