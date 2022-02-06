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
                is_frozen[current_tile] = true;
                i++;
            }
            current_tile++;
        }
    }

    Tetravex::Tetravex(unsigned size)
        : size(size)
        , board(size*size)
        , is_frozen(size*size, false)
    {}

    Tile::Tile() : up(-1), left(-1), right(-1), down(-1) {}

    char& Tile::operator[](int i) {
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

    std::ostream& operator<<(std::ostream& os, const Tetravex& t)
    {
        int size = t.size;
        for (unsigned j = 0; j < t.size; ++j)
        {
            for (unsigned i = 0; i < size; ++i)
                os << "  " << (int)t.board[j*size + i].up << "  |";
            os << '\n';
            for (unsigned i = 0; i < size; ++i)
                os << ' ' << (int)t.board[j*size + i].left
                   << ' ' << (int)t.board[j*size + i].right << " |";
            os << '\n';
            for (unsigned i = 0; i < size; ++i)
                os << "  " << (int)t.board[j*size + i].down << "  |";
            os << '\n';

            for (unsigned i = 0; i < t.size; ++i)
                os << "------";
            os << '\n';
        }
        return os;
    }
}
