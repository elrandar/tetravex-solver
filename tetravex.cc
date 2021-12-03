//
// Created by alexandre on 02/12/2021.
//

#include "tetravex.hh"

namespace tetrasolver {
    Tetravex::Tetravex(const std::string& input, unsigned int size)
            : size(size), board(std::vector<Tile>(size * size)) {
        int current_tile = 0;
        int i = 0;
        while (i < input.size())
        {
            // skip white
            while (input[i] == ' ' || input[i] == '\n')
                i++;

            board[current_tile].up = input[i] - '0';
            board[current_tile].left = input[i+1] - '0';
            board[current_tile].right = input[i+2] - '0';
            board[current_tile].down = input[i+3] - '0';
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
}
