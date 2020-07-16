//
// Created by rob on 7/16/2020.
//

#include "Instructions/A_Type.h"
#include "Instructions/Symbol.h"
#include "AsmLine.h"

#include "gtest/gtest.h"
#include "string_utils.h"

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
        "(ball.move$if_false0)"
};

TEST(ATypeIdentify, Positive) {
    //Should identify every string as an A-Type
    for (const auto &str : real_atypes) {
        //construct fake AsmLine.  The values for line and inst loc don't matter
        hackasm::AsmLine asml(-1, -1, str);
        EXPECT_TRUE(hackasm::A_Type::identify(asml));
    }
}

TEST(ATypeIdentify, Negative) {
    //Should identify every string as an A-Type
    for (const auto &str : fake_atypes) {
        //construct fake AsmLine.  The values for line and inst loc don't matter
        hackasm::AsmLine asml(-1, -1, str);
        EXPECT_FALSE(hackasm::A_Type::identify(asml));
    }
}