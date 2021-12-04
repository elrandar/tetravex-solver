//
// Created by alexandre on 02/12/2021.
//

#include "tetravex.hh"

namespace tetrasolver {
    Tetravex::Tetravex(const std::string &input, unsigned int size)
            : Tetravex(size) {
        int current_tile = 0;
        int i = 0;
        while (i < input.size()) {
            // skip white
            while (input[i] == ' ' || input[i] == '\n')
                i++;

            board[current_tile].up = input[i] - '0';
            board[current_tile].left = input[i + 1] - '0';
            board[current_tile].right = input[i + 2] - '0';
            board[current_tile].down = input[i + 3] - '0';
            i = i + 4;

            // skip white
            while (input[i] == ' ' || input[i] == '\n')
                i++;
            if (input[i] == '@') {
                board[current_tile].frozen = true;
                i++;
            }
            current_tile++;
        }
    }

    Tetravex::Tetravex(unsigned size) : size(size), board(std::vector<Tile>(size * size)) {}

    Tile::Tile() : up(-1), left(-1), right(-1), down(-1), frozen(false) {}

    int &Tile::operator[](int i) {
        switch (i) {
            case 0:
                return up;
            case 1:
                return left;
            case 2:
                return right;
            case 3:
                return down;
            default:
                throw std::invalid_argument("Operator [] for tiles only takes integer between 0 and 3 as input");
        }
    }
}
