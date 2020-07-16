//
// Created by rob on 7/16/2020.
//

#include <string_view>

#include "gtest/gtest.h"
#include "string_utils.h"

using namespace std::literals;

//Synthetic tests
TEST(TrimStringView, Left) {
    const std::string foo = "     foo     ";
    EXPECT_EQ("foo     "sv, trim_left(foo));
}

TEST(TrimStringView, Right) {
    const std::string foo = "     foo     ";
    EXPECT_EQ("     foo"sv, trim_right(foo));
}

TEST(TrimStringView, Both) {
    const std::string foo = "     foo     ";
    EXPECT_EQ("foo"sv, trim(foo));
}

TEST(TrimStringView, TabsLeft) {
    const std::string tabs = "\tfoo\t";
    EXPECT_EQ("foo\t"sv, trim_left(tabs));
}

TEST(TrimStringView, TabsRight) {
    const std::string tabs = "\tfoo\t";
    EXPECT_EQ("\tfoo"sv, trim_right(tabs));
}

TEST(TrimStringView, TabsBoth) {
    const std::string tabs = "\tfoo\t";
    EXPECT_EQ("foo"sv, trim(tabs));
}

TEST(TrimStringView, Mixed) {
    const std::string mixed = "\t  \t foo\t  \t ";
    EXPECT_EQ("foo\t  \t "sv, trim_left(mixed));
    EXPECT_EQ("\t  \t foo"sv, trim_right(mixed));
    EXPECT_EQ("foo"sv, trim(mixed));
}

TEST(TrimStringInplace, Test) {
    std::string str = "   foo   ";
    EXPECT_EQ("foo   ", trim_left(str));
}

TEST(DecommentStringView, Test) {
    const std::string foo = "  foo  //bar baz ban";
    EXPECT_EQ("  foo  "sv, decomment(foo));
}

TEST(DecommentStringInplace, Test) {
    std::string foo = "  foo  //bar baz ban";
    decomment(foo);
    EXPECT_EQ("  foo  ", foo);
}

TEST(DecommentStringInplace, EntireLine) {
    std::string foo = "//all line comment";
    decomment(foo);
    EXPECT_EQ("", foo);
}

//TODO: use actual source lines in tests