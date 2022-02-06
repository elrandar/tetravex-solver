//
// Created by alexandre on 02/12/2021.
//

#ifndef TETRAVEX_SOLVER_TETRAVEX_HH
#define TETRAVEX_SOLVER_TETRAVEX_HH

#include <ostream>
#include <vector>

namespace tetrasolver {
    struct Tile {
        char up;
        char left;
        char right;
        char down;

        Tile();

        char &operator[](int i);
    };

    class Tetravex {
    public:
        unsigned size;
        std::vector<Tile> board;
        std::vector<bool> is_frozen;

        Tetravex(unsigned size);

        Tetravex(const std::string &input, unsigned size);

        friend std::ostream& operator<<(std::ostream& os, const Tetravex& t);
    };
}

#endif //TETRAVEX_SOLVER_TETRAVEX_HH
