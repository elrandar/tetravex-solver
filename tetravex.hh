//
// Created by alexandre on 02/12/2021.
//

#ifndef TETRAVEX_SOLVER_TETRAVEX_HH
#define TETRAVEX_SOLVER_TETRAVEX_HH

#include <iostream>
#include <vector>
#include <ostream>

namespace tetrasolver {
    struct Tile {
        int up;
        int left;
        int right;
        int down;
        bool frozen;

        Tile();

        int &operator[](int i);
        bool operator==(const Tile& other);
        bool operator!=(const Tile& other);
    };

    class Tetravex {
    public:
        unsigned size;
        std::vector<Tile> board;

        Tetravex(unsigned size);

        Tetravex(const std::string &input, unsigned size);

        friend std::ostream & operator << (std::ostream &out, const Tetravex &tetra);
        bool operator==(const Tetravex &other);
    };
}

#endif //TETRAVEX_SOLVER_TETRAVEX_HH
