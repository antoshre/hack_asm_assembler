//
// Created by rob on 7/15/2020.
//

#include <bitset>
#include <cassert>
#include <utility>
#include <stdexcept>
#include <iostream>
#include "hackasm/Instructions/A_Type.h"
#include "hackasm/AsmLine.h"
#include "hackasm/AsmLine.h"
#include "hackasm/SymbolTable.h"
#include "ctre.hpp"

namespace hackasm {

    A_Type::A_Type(const AsmLine &l) {
        //Match "@<non-whitespace>"
        if (auto[m, v]=ctre::match<R"(@(\S+))">(l.inst); m) {
            value = v.to_view();
            line_loc = l.line_num;
            inst_loc = l.inst_num;
        } else {
            throw std::runtime_error("Cannot parse A-Type: " + l.inst);
        }
    }

    //Match "@<non-whitespace>"
    bool A_Type::identify(const AsmLine &l) {
        return ctre::match<R"(@\S+)">(l.inst);
    }

    std::ostream &operator<<(std::ostream &os, const A_Type &obj) {
        os << "A(" << obj.value << ")";
        return os;
    }

    std::string A_Type::to_binary_format(const SymbolTable& syms) const {
        auto v = syms[value];
        assert(v >= 0 && v < 32768);
        std::bitset<16> bits(v);
        return bits.to_string();
    }

    std::string A_Type::to_string() const {
        return "A(" + std::string(value) + ")";
    }

    std::string A_Type::to_string(const SymbolTable &syms) const {
        return "A(" + std::string(value) + " -> " + std::to_string(syms[value]) + ")";
    }
}