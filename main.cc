//
// Created by alexandre on 02/12/2021.
//

#include "tetravex.hh"
#include "io.hh"
#include "solver.hh"
#include "generate.hh"
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cout << "You must specify the input and output file";
        exit(1);
    }

    auto tetra = tetrasolver::generate_tetravex(2, 42, false);

//    auto tetra = tetrasolver::tetravex_from_file(argv[1]);

    auto solver = tetrasolver::Solver(tetra, 30000000);
    solver.solve();

    tetrasolver::tetravex_to_file(tetra, argv[2]);

    return 0;
}