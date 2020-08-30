//
// Created by rob on 7/16/2020.
//

#include <vector>
#include <string>

#include "hackasm/hackasm.h"

#include "gtest/gtest.h"

std::vector<std::string> real_ltypes = {
        "(LOOP)", "(END)", "(ball.move$if_false0)"
};

TEST(LType, PositiveIdentify) {
    //Should identify every string as an L-Type
    for (const auto &str : real_ltypes) {
        //construct fake AsmLine.  The values for line and inst loc don't matter for identification
        hackasm::AsmLine asml{-1, -1, str};
        EXPECT_TRUE(hackasm::L_Type::identify(asml)) << "Line: " << asml.inst;
    }
}