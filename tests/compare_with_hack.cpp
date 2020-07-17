//
// Created by rob on 7/16/2020.
//

#include <fstream>
#include <sstream>

#include "hackasm/AsmFile.h"
#include "hackasm/AST.h"

#include "gtest/gtest.h"

std::vector<std::string> asm_to_binary(const std::string &asm_filename) {
    std::ifstream file(asm_filename, std::ios::in);
    hackasm::AST ast{hackasm::AsmFile(file)};
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
    auto testee = asm_to_binary("../../examples/Add.asm");
    auto gold = read_file("../../examples/Add.hack");
    ASSERT_TRUE(testee.size() == gold.size());
    for (int i = 0; i < gold.size(); i++) {
        ASSERT_EQ(gold[i], testee[i]) << "Mismatch at line# " << i;
    }
}

TEST(PongL, Test) {
    auto testee = asm_to_binary("../../examples/PongL.asm");
    auto gold = read_file("../../examples/PongL.hack");
    ASSERT_TRUE(testee.size() == gold.size());
    for (int i = 0; i < gold.size(); i++) {
        ASSERT_EQ(gold[i], testee[i]) << "Mismatch at line# " << i;
    }
}

TEST(Pong, Test) {
    auto testee = asm_to_binary("../../examples/Pong.asm");
    auto gold = read_file("../../examples/Pong.hack");
    ASSERT_EQ(testee.size(), gold.size());
    for (int i = 0; i < gold.size(); i++) {
        ASSERT_EQ(gold[i], testee[i]) << "Mismatch at line# " << i;
    }
}