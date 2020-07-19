//
// Created by rob on 7/15/2020.
//

#ifndef HACK_TO_CPP_SYMBOL_H
#define HACK_TO_CPP_SYMBOL_H

#include <string>
#include <iostream>
#include <utility>
#include <string_view>

namespace hackasm {
    struct Symbol {
        std::string_view label; //actual text from the source
        int value; //the final value after being reified by a symbol table
        int line_loc; //line location in original source, zero-indexed
        int inst_loc; //location in the instruction stream, zero-indexed

        //TODO: simplify constructors.  Delegating down?
        //label, line location, instruction location
        Symbol() : label("<BADSYMBOL>"), line_loc(-1), inst_loc(-1), value(-1) {}

        Symbol(std::string_view _label, int _line, int _inst) : label(_label), line_loc(_line), inst_loc(_inst),
                                                                value(-1) {}

        Symbol(std::string_view _label, int _v, int _line, int _inst) : label(_label), line_loc(_line),
                                                                        inst_loc(_inst), value(_v) {}

        friend std::ostream &operator<<(std::ostream &os, const Symbol &obj) {
            //TODO: verbosity setting
            //os << obj.label << '@' << "(line=" << obj.line_loc << ",inst=" << obj.inst_loc << ")=" << obj.value;
            os << obj.label << "=" << obj.value;
            return os;
        }
    };
}

#endif //HACK_TO_CPP_SYMBOL_H
