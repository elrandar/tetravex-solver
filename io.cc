//
// Created by alexandre on 03/12/2021.
//

#include "io.hh"
#include <cmath>
#include <sstream>
#include <fstream>


namespace tetrasolver {

    Tetravex tetravex_from_file(const std::string &path) {
        std::ifstream file(path);
        std::stringstream buffer;
        buffer << file.rdbuf();

        auto content = buffer.str();
        int nb_lines = 1;
        for (int i = 0; i < content.size(); i++) {
            if (content[i] == '\n'
                && i + 1 < content.size()
                && content[i + 1] != '\n')
                nb_lines++;
        }

        auto sqrt_lines = static_cast<unsigned>(std::floor(sqrt(nb_lines)));
        if (sqrt_lines == 0)
            throw std::invalid_argument("Empty file given as input");
        else if (sqrt(nb_lines) == sqrt_lines) // Square root of nb of lines is integer
            return Tetravex(content, sqrt_lines);

        throw std::invalid_argument("Tetravex must be a square");
    }

    void tetravex_to_file(const Tetravex& tetra, const std::string &path)
    {
        std::ofstream file(path);

        for (int i = 0; i < tetra.board.size(); i++)
        {
            auto tile = tetra.board[i];
            file << tile.up << tile.left << tile.right << tile.down;
            if (i != tetra.board.size() - 1)
                file << '\n';
        }
        file.close();
    }
}