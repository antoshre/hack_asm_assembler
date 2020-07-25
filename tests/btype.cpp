//
// Created by rob on 7/22/20.
//

#include <vector>
#include <string>
#include <string_view>

#include "hackasm/hackasm.h"
#include "hackasm/string_utils.h"

#include "gtest/gtest.h"

std::vector<std::string> positive_match = {
        "0;JMP",
        "M+1;JGT",
        "D+A;JNE"
};

std::vector<std::string> negative_match = {
        "D=0"
        "AMD=-1"
        "M=D+A"
};

TEST(BType, PositiveIdentify) {
    //Should identify every string as an A-Type
    for (const auto &str : positive_match) {
        //construct fake AsmLine.  The values for line and inst loc don't matter
        hackasm::AsmLine asml{-1, -1, str};
        EXPECT_TRUE(hackasm::B_Type::identify(asml)) << "Line: " << asml.inst;
    }
}

TEST(BType, NegativeIdentify) {
    //Should identify every string as an A-Type
    for (const auto &str : negative_match) {
        //construct fake AsmLine.  The values for line and inst loc don't matter
        hackasm::AsmLine asml{-1, -1, str};
        EXPECT_FALSE(hackasm::B_Type::identify(asml)) << "Line: " << asml.inst;
    }
}