//
// Created by rob on 7/14/2020.
//

#ifndef HACK_TO_CPP_ASMFILE_H
#define HACK_TO_CPP_ASMFILE_H

#include "AsmLine.h"

#include <vector>
#include <string>
#include <istream>
#include <iosfwd>

namespace hackasm {
    struct AsmFile {
        std::vector<std::string> source;
        std::vector<AsmLine> instructions;

        explicit AsmFile(std::istream &);

        friend std::ostream &operator<<(std::ostream &, const AsmFile &);
    };
}

#endif //HACK_TO_CPP_ASMFILE_H
