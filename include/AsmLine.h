//
// Created by rob on 7/16/2020.
//

#ifndef HACK_TO_CPP_ASMLINE_H
#define HACK_TO_CPP_ASMLINE_H

#include <string>

namespace hackasm {
    struct AsmLine {
        //The line number from the original source, comments and whitespace included
        int line_num;
        //The logical instruction number
        int inst_num;
        //The assembly line, stripped of excess whitespace and comments
        std::string inst;
    };
}

#endif //HACK_TO_CPP_ASMLINE_H
