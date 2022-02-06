//
// Created by alexandre on 02/12/2021.
//

#include "io.hh"
#include "solver.hh"
#include <iostream>

int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cout << "You must specify the input and output file";
        exit(1);
    }

    auto tetra = tetrasolver::tetravex_from_file(argv[1]);

    auto solver = tetrasolver::Solver(tetra, 10000000);

    solver.solve(true);

    tetrasolver::tetravex_to_file(tetra, argv[2]);

    return 0;
}
