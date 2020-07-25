//
// Created by rob on 7/22/20.
//

#include "hackasm/Instructions/B_Type.h"
#include "hackasm/AsmLine.h"
#include "hackasm/SymbolTable.h"
#include <stdexcept>
#include <iostream>
#include <bitset>
#include "ctre.hpp"
namespace hackasm {


    B_Type::B_Type(const hackasm::AsmLine &l) {
        inst_loc = l.inst_num;
        line_loc = l.line_num;
        if (auto [m,c,j] = ctre::match<R"((\S+);(\S+))">(l.inst); m) {
            comp_mnemonic = c.to_view();
            jump_mnemonic = j.to_view();
            return;
        }
        throw std::runtime_error("Cannot parse B-Type: " + l.inst);
    }

    bool B_Type::identify(const AsmLine &l) {
        return ctre::match<R"(\S+;\S+)">(l.inst);
    }

    namespace detail {
        extern uint16_t comp(const std::string_view);
        extern uint16_t jump(const std::string_view);
    }

    std::string B_Type::to_binary_format(const SymbolTable& _) const {
        auto c = detail::comp(comp_mnemonic);
        auto j = detail::jump(jump_mnemonic);
        std::bitset<16> bits = 0xE000;
        bits |= c | j;
        return bits.to_string();
    }

    std::ostream &operator<<(std::ostream &os, const B_Type &obj) {
        os << "B(" << obj.comp_mnemonic << ";" << obj.jump_mnemonic << ")";
        return os;
    }

    std::string B_Type::to_string() const {
        return "B(" + std::string(comp_mnemonic) + ";" + std::string(jump_mnemonic) + ")";
    }

    std::string B_Type::to_string(const SymbolTable &) const {
        return to_string();
    }
}