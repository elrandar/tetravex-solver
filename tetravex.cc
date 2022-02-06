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
    bool Tetravex::operator==(const Tetravex &other) {
        if (size != other.size)
            return false;

        for (int i = 0; i < board.size(); i++)
        {
            if (board[i] != other.board[i])
                return false;
        }

        return true;
    }


    std::ostream &operator<<(std::ostream &out, const Tetravex &tetra) {

        for (int i = 0; i < tetra.size; i++)
        {

            // que des plus
            for (int j = 0; j < tetra.size * 6; j++)
                out << '-';
            // top
            out << "-\n";
            for (int j = 0; j < tetra.size; j++)
                out << "|  " << tetra.board[i * tetra.size + j].up << "  ";
            // left right
            out << "|\n";
            for (int j = 0; j < tetra.size; j++)
                out << "| " << tetra.board[i * tetra.size + j].left << " "
                            << tetra.board[i * tetra.size + j].right << " ";
            out << "|\n";
            // bot
            for (int j = 0; j < tetra.size; j++)
                out << "|  " << tetra.board[i * tetra.size + j].down << "  ";
            out << "|\n";
        }
        for (int j = 0; j < tetra.size * 6; j++)
            out << '-';
        out << "-\n";

        return out;
    }


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

    bool Tile::operator==(const Tile &other) {
        auto vec1 = std::vector<int>({left, right, up, down});
        auto vec2 = std::vector<int>({other.left, other.right, other.up, other.down});

        for (int i = 0; i < vec1.size(); i++)
        {
            if (vec1[i] != vec2[i])
                return false;
        }

        return true;
    }

    bool Tile::operator!=(const Tile &other) {
        return !operator==(other);
    }
}
