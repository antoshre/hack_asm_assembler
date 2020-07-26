//
// Created by rob on 7/14/2020.
//

#ifndef HACK_TO_CPP_SYMBOLTABLE_H
#define HACK_TO_CPP_SYMBOLTABLE_H

#include "hackasm/Instruction.h"
#include "hackasm/string_utils.h"

#include <unordered_map>
#include <map>
#include <iosfwd>
#include <string>


namespace hackasm {

    class Symbol;

    //TODO: refactor this interace to be more map-like
    class SymbolTable {
        std::unordered_map<std::string, int> predefined;
        std::unordered_map<std::string, int> labels;
        std::map<std::string, int> symbols;

        bool symbols_are_dirty = false;
        void renumber_symbols();


    public:
        //Set up predefined symbols table
        //TODO: use frozen map instead
        SymbolTable();

        //Insert symbol as a label, saving the instruction location
        void insert_label(const std::string&, int);
        void insert_label(std::string_view, int);
        void insert(const std::string&);
        void insert(std::string_view);



        int operator[](const std::string&) const;
        int operator[](std::string_view) const;

        friend std::ostream &operator<<(std::ostream &, const SymbolTable &);

        const std::unordered_map<std::string, int>& get_labels() const;
    };
}

#endif //HACK_TO_CPP_SYMBOLTABLE_H
