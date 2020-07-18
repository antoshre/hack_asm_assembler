//
// Created by rob on 7/11/2020.
//

#ifndef HACK_ASSEMBLER_STRING_UTILS_H
#define HACK_ASSEMBLER_STRING_UTILS_H

#include <string_view>
#include <algorithm>
#include <iterator>

//Common substring operations on string_view

//Trim whitespace from left of sv
inline std::string_view trim_left(std::string_view sv) {
    //Trim whitespace off of left side of sv.
    //"      herp  " -> "herp  "
    auto start = std::find_if(sv.begin(), sv.end(), [](const char c) { return !isspace(c); });
    auto len = std::distance(start, sv.end());
    //TODO: There must be a clearer way to do this.
    return {start, static_cast<std::string_view::size_type>(len)};
}

//Trim whitespace from right of sv
inline std::string_view trim_right(std::string_view sv) {
    //Trim whitespace off of right side of sv
    auto end = std::find_if(sv.rbegin(), sv.rend(), [](const char c) { return !isspace(c); }).base();
    auto len = std::distance(sv.begin(), end);
    return {sv.begin(), static_cast<std::string_view::size_type>(len)};
}

//Trim whitespace from both sides of sv
inline std::string_view trim(std::string_view sv) {
    return trim_left(trim_right(sv));
}

//Remove C++ "//..." style comments from sv
inline std::string_view decomment(std::string_view sv) {
    auto pos = sv.find_first_of("//");
    return sv.substr(0, pos);
}

//Trim string in-place
inline void trim_inplace(std::string &s) {
    auto start = std::find_if(s.begin(), s.end(), [](const char c) { return !isspace(c); });
    s.erase(s.begin(), start);
    auto end = std::find_if(s.rbegin(), s.rend(), [](const char c) { return !isspace(c); }).base();
    s.erase(end, s.end());
}

//Comment string in-place
inline void decomment(std::string &s) {
    auto pos = s.find_first_of("//");
    //TODO: is this if really necessary?
    if (pos != std::string::npos) {
        s.erase(s.begin() + pos, s.end());
    }
}

#endif //HACK_ASSEMBLER_STRING_UTILS_H
