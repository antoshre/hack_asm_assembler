//
// Created by rob on 7/15/2020.
//

#ifndef HACK_TO_CPP_INSTRUCTION_H
#define HACK_TO_CPP_INSTRUCTION_H

#include <variant>
#include "Instructions/A_Type.h"
#include "Instructions/L_Type.h"
#include "Instructions/C_Type.h"
#include "Instructions/Symbol.h"

namespace hackasm {
    using Instruction = std::variant<A_Type, L_Type, C_Type>;
}
#endif //HACK_TO_CPP_INSTRUCTION_H
