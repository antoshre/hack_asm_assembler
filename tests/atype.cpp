//
// Created by rob on 7/16/2020.
//

#include "hackasm/hackasm.h"
#include "hackasm/string_utils.h"

#include "gtest/gtest.h"

//access string_view ""sv operator
using namespace std::literals;

std::vector<std::string> real_atypes = {
        "@i", "@sum", "@100", "@END", "@26561", "@R15", "@END_LT", "@RET_ADDRESS_CALL1", "@math.multiply",
        "@ball.move$if_true0", "@ball.move$if_false0"
};

std::vector<std::string> fake_atypes = {
        "0;JMP",
        "AM=M-1",
        "(RET_ADDRESS_LT5)",
        "(ball.move$if_false0)",
};

TEST(AType, PositiveIdentify) {
    //Should identify every string as an A-Type
    for (const auto &str : real_atypes) {
        //construct fake AsmLine.  The values for line and inst loc don't matter
        hackasm::AsmLine asml{-1, -1, str};
        EXPECT_TRUE(hackasm::A_Type::identify(asml)) << "Line: " << asml.inst;
    }
}

TEST(AType, NegativeIdentify) {
    //Should identify every string as an A-Type
    for (const auto &str : fake_atypes) {
        //construct fake AsmLine.  The values for line and inst loc don't matter for identification
        hackasm::AsmLine asml{-1, -1, str};
        EXPECT_FALSE(hackasm::A_Type::identify(asml)) << "Line: " << asml.inst;
    }
}

/*
TEST(AType, ToBinary) {
    //Create dummy line to populate instruction
    hackasm::AsmLine line{-1, -1, "@100"};
    hackasm::A_Type inst(line);
    //Fix symbol to have dummy values for testing
    inst.value = "100";
    EXPECT_EQ("0000000000101010", inst.to_binary_format());
    inst.s.value = 21845;
    EXPECT_EQ("0101010101010101", inst.to_binary_format());
    inst.s.value = 32767;
    EXPECT_EQ("0111111111111111", inst.to_binary_format());
}
*/