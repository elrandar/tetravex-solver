//
// Created by alexandre on 04/12/2021.
//

#include "generate.hh"
#include "../solver.hh"
#include <random>
#include <algorithm>

namespace tetrasolver {
    bool is_valid(int side, int index, int size) {
        switch (side) {
            case 0:
                return index / size >= 1;
            case 1:
                return index % size > 0;
            case 2:
                return index % size < size - 1;
            case 3:
                return index / size < (size * size) - size;
            default:
                throw std::invalid_argument("Side must be between 0 and 3");
        }
    }

    Tetravex generate_tetravex(unsigned size, int seed, bool shuffle) {
        auto tetra = Tetravex(size);
        auto r_e = std::default_random_engine(seed);
        auto distrib = std::uniform_int_distribution(0, 9);

        std::vector<std::pair<int, int>> neighbor_indexes({std::make_pair(-(int) size, 3),
                                                           std::make_pair(-1, 2),
                                                           std::make_pair(+1, 1),
                                                           std::make_pair((int) size, 0)});

        for (int i = 0; i < tetra.board.size(); i++) { // for each tile
            auto &tile = tetra.board[i];

            for (int j = 0; j < 4; j++) { // for each side
                auto &side = tile[j];
                auto pair = neighbor_indexes[j];
                if (side == -1) { // if side not filled yet
                    side = distrib(r_e);
                    // if matching side
                    if (is_valid(j, i, (int) size))
                        tetra.board[i + pair.first][pair.second] = side;
                }
            }
        }

        if (shuffle)
        {
            int i = 0;
            while (Solver::is_solved(tetra)) {
                std::mt19937 g(seed + i);
                std::shuffle(tetra.board.begin(), tetra.board.end(), g);
                i++;
            }
        }
        return tetra;
    }
}