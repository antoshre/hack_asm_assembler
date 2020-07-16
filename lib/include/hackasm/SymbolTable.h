//
// Created by rob on 7/14/2020.
//

#ifndef HACK_TO_CPP_SYMBOLTABLE_H
#define HACK_TO_CPP_SYMBOLTABLE_H

#include "hackasm/Instruction.h"

#include <unordered_map>
#include <iosfwd>
#include <string>


namespace hackasm {

    class Symbol;

    //TODO: refactor this interace to be more map-like
    class SymbolTable {
        std::unordered_map<std::string, int> predefined;
        std::unordered_map<std::string, int> labels;
        std::unordered_map<std::string, int> symbols;
        int auto_symbol_offset = 0x0010;

        //Fill out symbol with information from the table
        //If it's a new symbol, add it to symbols at automatic location
        void reify(Symbol &);

    public:
        //Set up predefined symbols table
        //TODO: use frozen map instead
        SymbolTable();

        //Insert symbol as a label, saving the instruction location
        void insert_label(const Symbol &);

        //Fill out Instruction with information from the table
        void reify(Instruction &);

        friend std::ostream &operator<<(std::ostream &, const SymbolTable &);
    };
}

#endif //HACK_TO_CPP_SYMBOLTABLE_H
