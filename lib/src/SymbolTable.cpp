//
// Created by rob on 7/14/2020.
//

#include "hackasm/SymbolTable.h"

#include <iostream>
#include <utility>

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



    void SymbolTable::insert_label(const std::string &s, int i) {
        if (predefined.contains(s)) {
            //It's a predefined symbol, do nothing
            return;
        }
        if (labels.contains(s)) {
            //throw std::runtime_error("Label defined multiple times: " + s);
            return;
        } else {
            //It's a new label.  Erase it from symbols, if it exists
            if (symbols.contains(s)) {
                symbols.erase(s);
                //Erasure happened. Symbols must be renumbered
                renumber_symbols();
            }
            labels.emplace(s,i);
        }
    }

    void SymbolTable::insert_label(std::string_view sv, int i) {
        insert_label( std::string(sv), i);
    }

    void SymbolTable::insert(const std::string &s) {
        if (is_integer_constant(s)) {
            //Integer constants will be parsed on retrieval, don't store
            return;
        }
        if (predefined.contains(s) || labels.contains(s) || symbols.contains(s)) {
            //It's already known, do nothing
            return;
        }
        static int auto_symbol_offset = 0x0010;
        symbols.emplace(s, auto_symbol_offset++);
    }

    void SymbolTable::insert(std::string_view sv) {
        insert( std::string(sv) );
    }

    void SymbolTable::renumber_symbols() {
        //TODO: auto-detect offset by lowest value in map
        int auto_symbol_offset = 0x0010;
        for (auto& [k,v] : symbols) {
            v = auto_symbol_offset++;
        }
    }


    int SymbolTable::operator[](const std::string &s) const {
        if (predefined.find(s) != predefined.end()) {
            return predefined.at(s);
        }
        if (labels.find(s) != labels.end()) {
            return labels.at(s);
        }
        if (symbols.find(s) != symbols.end()) {
            return symbols.at(s);
        }
        if (is_integer_constant(s)) {
            return std::stoi(s);
        }
        throw std::runtime_error("Bad symbol lookup: " + s);
    }

    int SymbolTable::operator[](std::string_view sv) const {
        return operator[](std::string(sv));
    }


    /*
    std::unordered_map<std::string, int> SymbolTable::get_labels() const {
        return std::as_const(labels);
    }
    */

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

    const std::unordered_map<std::string, int> &SymbolTable::get_labels() const {
        return std::as_const(labels);
    }
}
