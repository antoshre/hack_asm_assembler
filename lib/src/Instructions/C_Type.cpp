//
// Created by rob on 7/15/2020.
//

#include "hackasm/Instructions/C_Type.h"
#include "hackasm/AsmLine.h"
#include "ctre.hpp"

namespace hackasm {

    bool C_Type::identify(const AsmLine &l) {
        if (ctre::match<R"(\S+=\S+)">(l.inst)) {
            return true;
        }
        if (ctre::match<R"(\S+;\S+)">(l.inst)) {
            return true;
        }
        return false;
    }

    C_Type::C_Type(const AsmLine &l) {
        if (auto[m, d, c]=ctre::match<R"((\S+)=(\S+))">(l.inst); m) {
            dest_mnemonic = std::string(d.to_view());
            comp_mnemonic = std::string(c.to_view());
            jump_mnemonic = "null";
            return;
        }
        if (auto[m, c, j]=ctre::match<R"((\S+);(\S+))">(l.inst); m) {
            dest_mnemonic = "null";
            comp_mnemonic = std::string(c.to_view());
            jump_mnemonic = std::string(j.to_view());
            return;
        }

        throw std::runtime_error("Cannot parse C-Type: " + l.inst);
    }

    std::ostream &operator<<(std::ostream &os, const C_Type &obj) {
        os << "C(";
        if (obj.dest_mnemonic != "null") {
            os << obj.dest_mnemonic << "=" << obj.comp_mnemonic;
        } else {
            os << obj.comp_mnemonic << " ; " << obj.jump_mnemonic;
        }
        os << ")";
        return os;
    }

}