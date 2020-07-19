//
// Created by rob on 7/15/2020.
//
#include <bitset>

#include "hackasm/Instructions/C_Type.h"
#include "hackasm/AsmLine.h"
#include "frozen/string.h"
#include "frozen/unordered_map.h"
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
        inst_loc = l.inst_num;
        line_loc = l.line_num;
        if (auto[m, d, c]=ctre::match<R"((\S+)=(\S+))">(l.inst); m) {
            dest_mnemonic = d;
            comp_mnemonic = c;
            jump_mnemonic = "null";
            return;
        }
        if (auto[m, c, j]=ctre::match<R"((\S+);(\S+))">(l.inst); m) {
            dest_mnemonic = "null";
            comp_mnemonic = c;
            jump_mnemonic = j;
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

    namespace detail {
        uint16_t dest(const std::string_view d) {
            constexpr frozen::unordered_map<frozen::string, int, 8> dmap = {
                    {"null", 0b0000000000000000},
                    {"M",    0b0000000000001000},
                    {"D",    0b0000000000010000},
                    {"MD",   0b0000000000011000},
                    {"A",    0b0000000000100000},
                    {"AM",   0b0000000000101000},
                    {"AD",   0b0000000000110000},
                    {"AMD",  0b0000000000111000}
            };
            const frozen::string f(d.data(), d.size());
            return dmap.at(f);
        }

        uint16_t comp(const std::string_view c) {
            constexpr frozen::unordered_map<frozen::string, int, 28> cmap = {
                    {"0",   0b0000101010000000},
                    {"1",   0b0000111111000000},
                    {"-1",  0b0000111010000000},
                    {"D",   0b0000001100000000},
                    {"A",   0b0000110000000000},
                    {"!D",  0b0000001101000000},
                    {"!A",  0b0000110001000000},
                    {"-D",  0b0000001111000000},
                    {"-A",  0b0000110011000000},
                    {"D+1", 0b0000011111000000},
                    {"A+1", 0b0000110111000000},
                    {"D-1", 0b0000001110000000},
                    {"A-1", 0b0000110010000000},
                    {"D+A", 0b0000000010000000},
                    {"D-A", 0b0000010011000000},
                    {"A-D", 0b0000000111000000},
                    {"D&A", 0b0000000000000000},
                    {"D|A", 0b0000010101000000},
                    {"M",   0b0001110000000000},
                    {"!M",  0b0001110001000000},
                    {"-M",  0b0001110011000000},
                    {"M+1", 0b0001110111000000},
                    {"M-1", 0b0001110010000000},
                    {"D+M", 0b0001000010000000},
                    {"D-M", 0b0001010011000000},
                    {"M-D", 0b0001000111000000},
                    {"D&M", 0b0001000000000000},
                    {"D|M", 0b0001010101000000}
            };
            const frozen::string f{c.data(), c.size()};
            return cmap.at(f);
        }

        uint16_t jump(const std::string_view j) {
            constexpr frozen::unordered_map<frozen::string, int, 8> jmap = {
                    {"null", 0b0000000000000000},
                    {"JGT",  0b0000000000000001},
                    {"JEQ",  0b0000000000000010},
                    {"JGE",  0b0000000000000011},
                    {"JLT",  0b0000000000000100},
                    {"JNE",  0b0000000000000101},
                    {"JLE",  0b0000000000000110},
                    {"JMP",  0b0000000000000111}
            };
            const frozen::string f{j.data(), j.size()};
            if (jmap.find(f) != jmap.end()) {
                return jmap.at(f);
            } else {
                throw std::logic_error("Jump mnemonic not found in lookup table");
            }
        }
    }

    std::string C_Type::to_binary_format() const {
        std::bitset<16> bits(0xE000);
        auto dest = detail::dest(dest_mnemonic);
        auto comp = detail::comp(comp_mnemonic);
        auto jump = detail::jump(jump_mnemonic);
        bits |= dest | comp | jump;
        return bits.to_string();
    }

}