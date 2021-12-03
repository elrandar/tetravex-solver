//
// Created by alexandre on 02/12/2021.
//

#ifndef TETRAVEX_SOLVER_TETRAVEX_HH
#define TETRAVEX_SOLVER_TETRAVEX_HH

#include <iostream>

class Tile {
    int up;
    int left;
    int right;
    int down;
};

template<unsigned T>
class Tetravex {
private:
    Tile board[T*T];

public:
    Tetravex()
    {

    };
    Tetravex(std::string input);
};


#endif //TETRAVEX_SOLVER_TETRAVEX_HH
