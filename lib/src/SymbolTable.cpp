//
// Created by rob on 7/14/2020.
//

#include "hackasm/SymbolTable.h"

#include "hackasm/Instructions/A_Type.h"
#include "hackasm/Instructions/L_Type.h"
#include "hackasm/Instructions/C_Type.h"
#include "hackasm/Instructions/Symbol.h"
#include "hackasm/Instruction.h"

#include <iostream>
#include <variant>

#include "ctre.hpp"

namespace hackasm {

    SymbolTable::SymbolTable() {
        /*
         * Label (dec) (hex)
         * SP 0 0x0000
         * LCL 1 0x0001
         * ARG 2 0x0002
         * THIS 3 0x0003
         * THAT 4 0x0004
         * R0-R15 0-15 0x0000-f
         * SCREEN 16384 0x4000
         * KBD 24576 0x6000
         */
        predefined.insert({"SP", 0x0000});
        predefined.insert({"LCL", 0x0001});
        predefined.insert({"ARG", 0x0002});
        predefined.insert({"THIS", 0x0003});
        predefined.insert({"THAT", 0x0004});
        predefined.insert({"SCREEN", 0x4000});
        predefined.insert({"KBD", 0x6000});

        //R0 - R15
        for (int i = 0; i < 16; i++) {
            predefined.insert({"R" + std::to_string(i), i});
        }
    }

    std::ostream &operator<<(std::ostream &os, const SymbolTable &obj) {
        os << "Labels:\n";
        for (const auto&[key, val] : obj.labels) {
            os << key << " = " << val << '\n';
        }
        os << "Symbols:\n";
        for (const auto&[key, val] : obj.symbols) {
            os << key << " = " << val << '\n';
        }
        return os;
    }

    void SymbolTable::insert_label(const Symbol &s) {
        if (predefined.find(s.label) == predefined.end()) {
            //TODO: verbosity setting
            //std::cout << "Label found: " << s.label << " @ " << s.inst_loc << '\n';
            labels.insert({s.label, s.inst_loc});
        }
    }

    void SymbolTable::reify(Instruction &i) {
        struct Reifier {
            SymbolTable &syms;

            explicit Reifier(SymbolTable &s) : syms(s) {}

            void operator()(A_Type &a) { syms.reify(a.s); }

            void operator()(L_Type &l) { syms.reify(l.s); }

            void operator()(C_Type &c) {}
        };
        std::visit(Reifier(*this), i);
    }

    void SymbolTable::reify(Symbol &s) {
        //Is it an integer constant?
        if (ctre::match<R"(\d+)">(s.label)) {
            s.value = std::stoi(s.label);
            return;
        }
        if (predefined.find(s.label) != predefined.end()) {
            s.value = predefined.at(s.label);
            return;
        }
        if (labels.find(s.label) != labels.end()) {
            s.inst_loc = labels.at(s.label);
            s.value = labels.at(s.label);
            return;
        }
        if (symbols.find(s.label) != symbols.end()) {
            s.value = symbols.at(s.label);
        } else {
            //it's unknown, insert it as an automatic symbol
            symbols.insert({s.label, auto_symbol_offset});
            s.value = auto_symbol_offset;
            //bump the offset for the next auto symbol
            auto_symbol_offset++;
        }
    }
}
