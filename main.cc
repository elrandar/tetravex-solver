//
// Created by alexandre on 02/12/2021.
//

#include "tetravex.hh"
#include "io.hh"
#include <iostream>

int main(int argc, char** argv)
{
    auto tetra = tetrasolver::tetravex_from_file("../input.txt");
    std::cout << "1";

    tetrasolver::tetravex_to_file(tetra, "out.txt");
    return 0;
}