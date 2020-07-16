//
// Created by rob on 7/14/2020.
//

#include "AST.h"

#include "Instructions/Symbol.h"
#include "SymbolTable.h"

#include <utility>
#include <iostream>
#include <variant>

#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <ctre.hpp>

using namespace boost;

namespace hackasm {

    //TODO: clean up somehow
    Instruction parse(const AsmLine &s) {
        if (A_Type::identify(s)) {
            return A_Type(s);
        }
        if (L_Type::identify(s)) {
            return L_Type(s);
        }
        if (C_Type::identify(s)) {
            return C_Type(s);
        }

        throw std::runtime_error("Cannot parse assembly line: " + s.inst);
    }

    AST::AST(AsmFile f) : assembly(std::move(f)) {
        //TODO: switch to std::ranges
        //Parse assembly source to instructions
        auto insts = assembly.instructions | adaptors::transformed([](AsmLine &a) { return parse(a); });
        boost::copy(insts, std::back_inserter(listing));

        //First pass: extract all labels
        auto labels = listing |
                      //select only L-Type instructions
                      adaptors::filtered([](Instruction &i) { return std::holds_alternative<L_Type>(i); }) |
                      //convert Instruction to L-Type
                      adaptors::transformed([](Instruction &i) { return std::get<L_Type>(i); }) |
                      //extract symbol from L-Type
                      adaptors::transformed([](const L_Type &l) { return l.s; });

        boost::for_each(labels, [&](const Symbol &s) {
            this->symbols.insert_label(s);
        });

        //Second pass: reify all instructions
        //TODO: change to reifying symbols instead.  Extract symbols in range op
        boost::for_each(listing, [&](Instruction &i) {
            symbols.reify(i);
        });
    }

    std::ostream &operator<<(std::ostream &os, const AST &obj) {
        os << "AST:\n";
        boost::for_each(obj.listing, [&](const Instruction &i) {
            std::visit([&](auto e) { os << e << '\n'; }, i);
        });
        os << "Symbol Table:\n";
        os << obj.symbols;
        return os;
    }
}
