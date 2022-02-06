//
// Created by alexandre on 03/12/2021.
//

#ifndef TETRAVEX_SOLVER_IO_HH
#define TETRAVEX_SOLVER_IO_HH

#include "tetravex.hh"
namespace tetrasolver {
    Tetravex tetravex_from_file(const std::string &path);
    void tetravex_to_file(const Tetravex& tetra, const std::string &path);
    std::string tetravex_to_str(const Tetravex& tetra);
}

#endif //TETRAVEX_SOLVER_IO_HH
