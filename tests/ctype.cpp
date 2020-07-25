//
// Created by rob on 7/16/2020.
//

#include "hackasm/hackasm.h"

#include "gtest/gtest.h"

TEST(CType, ToBinary) {
    //Symbol table required for signature, but not used
    hackasm::SymbolTable syms;
    //Create dummy line to populate instruction
    hackasm::AsmLine line{-1, -1, "D=1"};
    hackasm::C_Type inst(line);
    //Fix symbol to have dummy values for testing
    inst.dest_mnemonic = "D";
    inst.comp_mnemonic = "0";
    EXPECT_EQ("1110101010010000", inst.to_binary_format(syms));

    inst.dest_mnemonic = "AMD";
    inst.comp_mnemonic = "D|M";
    EXPECT_EQ("1111010101111000", inst.to_binary_format(syms));
}