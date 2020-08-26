//
// Created by rob on 7/16/2020.
//

#include <fstream>
#include <sstream>

#include "hackasm/hackasm.h"
#include "hackasm/string_utils.h"

#include "gtest/gtest.h"

std::vector<std::string> asm_to_binary(const std::string &asm_filename) {
    std::ifstream file(asm_filename, std::ios::in);
    hackasm::AST ast{file};
    return ast.to_binary();
}

std::vector<std::string> read_file(const std::string &filename) {
    std::ifstream file(filename, std::ios::in);
    std::vector<std::string> contents{};
    std::string temp;
    while (std::getline(file, temp)) {
        contents.push_back(temp);
    }
    return contents;
}

TEST(Add, Test) {
    auto dut = asm_to_binary("../../examples/Add.asm");
    auto gold = read_file("../../examples/Add.hack");
    //If the line count doesn't match, fail immedediately.  Iterating over will likely cause OOB-access
    ASSERT_EQ(dut.size(), gold.size());
    //TODO: use std::ranges to get something like for(const auto& [line, comp] : zip(dut, gold))
    for (int i = 0; i < gold.size(); i++) {
        //Trimming required to handle impedance mismatch between system line endings.
        //IE Windows "/r/n" endings leave the '/r' when run through std::getline
        //TODO: handle this on the input end instead of in the test
        ASSERT_EQ(trim(gold[i]), trim(dut[i])) << "Mismatch at line# " << i;
    }
}

TEST(PongL, Test) {
    auto testee = asm_to_binary("../../examples/PongL.asm");
    auto gold = read_file("../../examples/PongL.hack");
    ASSERT_EQ(testee.size() , gold.size());
    for (int i = 0; i < gold.size(); i++) {
        ASSERT_EQ(trim(gold[i]), trim(testee[i])) << "Mismatch at line# " << i;
    }
}

TEST(Pong, Test) {
    auto testee = asm_to_binary("../../examples/Pong.asm");
    auto gold = read_file("../../examples/Pong.hack");
    ASSERT_EQ(testee.size(), gold.size());
    for (int i = 0; i < gold.size(); i++) {
        ASSERT_EQ(trim(gold[i]), trim(testee[i])) << "Mismatch at line# " << i;
    }
}