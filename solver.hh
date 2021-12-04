//
// Created by alexandre on 03/12/2021.
//

#ifndef TETRAVEX_SOLVER_SOLVER_HH
#define TETRAVEX_SOLVER_SOLVER_HH

#include "tetravex.hh"
#include <random>


namespace tetrasolver {
    class Solver {
        Tetravex &tetravex;
        int k_max;

        std::vector<int> indices_map;

        std::default_random_engine random_engine;
        std::uniform_int_distribution<int> distribution;

        float temperature(float frac);
        std::pair<int, int> random_permutation();
        void generate_map();
        int compute_cost(const std::pair<int, int> &permutation);
        void apply_permutation(const std::pair<int, int> &permutation);
        static float acceptance_probability(int cost, int new_cost, float temp);
    public:

        bool is_solved() const;

        void solve();

        explicit Solver(Tetravex &tetravex, int k_max);
    };
}


#endif //TETRAVEX_SOLVER_SOLVER_HH
