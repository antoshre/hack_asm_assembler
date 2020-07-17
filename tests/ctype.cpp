//
// Created by rob on 7/16/2020.
//

#include "hackasm/Instructions/C_Type.h"
#include "hackasm/Instructions/Symbol.h"
#include "hackasm/AsmLine.h"

#include "gtest/gtest.h"
#include "hackasm/string_utils.h"

TEST(CType, ToBinary) {
    //Create dummy line to populate instruction
    hackasm::AsmLine line{-1, -1, "D=1"};
    hackasm::C_Type inst(line);
    //Fix symbol to have dummy values for testing
    inst.dest_mnemonic = "D";
    inst.comp_mnemonic = "0";
    inst.jump_mnemonic = "null";
    EXPECT_EQ("1110101010010000", inst.to_binary_format());

    inst.dest_mnemonic = "AMD";
    inst.comp_mnemonic = "D|M";
    inst.jump_mnemonic = "null";
    EXPECT_EQ("1111010101111000", inst.to_binary_format());

    inst.dest_mnemonic = "null";
    inst.comp_mnemonic = "M-1";
    inst.jump_mnemonic = "JLT";
    EXPECT_EQ("1111110010000100", inst.to_binary_format());
}