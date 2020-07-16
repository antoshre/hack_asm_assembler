//
// Created by rob on 7/14/2020.
//

#include "hackasm/AsmFile.h"
#include "hackasm/Instructions/L_Type.h"
#include "hackasm/string_utils.h"

#include <iterator>
#include <fstream>

#include <boost/range/adaptor/indexed.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>

using namespace boost;


namespace hackasm {

    AsmFile::AsmFile(std::istream &file) {
        if (!file) {
            throw std::runtime_error("Cannot access file stream.");
        }

        std::string temp;
        while (std::getline(file, temp)) {
            source.push_back(temp);
        }

        //Fun with Boost ranges!
        auto ins = source |
                   adaptors::indexed() | //add source line numbers
                   //remove comments, trim_inplace excess whitespace
                   adaptors::transformed([](auto e) {
                       trim_inplace(e.value());
                       decomment(e.value());
                       return e;
                   }) |
                   //remove empty lines
                   adaptors::filtered([](auto e) { return e.value().length() > 0; }) |
                   //convert to AsmLines
                   adaptors::transformed([](auto elem) {
                       return AsmLine{(int) elem.index(), -1, elem.value()};
                   });

        //copy range to instructions vector
        boost::copy(ins, std::back_inserter(instructions));

        //Calulate correct instruction numbering
        //L-Types are not real and should be skipped
        int current_inst = 0;
        for (auto &asmline : instructions) {
            asmline.inst_num = current_inst;
            if (!L_Type::identify(asmline)) {
                current_inst++;
            }
        }
    }

    std::ostream &operator<<(std::ostream &os, const AsmFile &obj) {
        for (const auto&[lnum, inum, line] : obj.instructions) {
            os << lnum << ',' << inum << '|' << line << '\n';
        }
        return os;
    }

}
