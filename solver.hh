//
// Created by alexandre on 03/12/2021.
//

#ifndef TETRAVEX_SOLVER_SOLVER_HH
#define TETRAVEX_SOLVER_SOLVER_HH

#include "tetravex.hh"
#include <random>


namespace tetrasolver {
    class Solver {
        Tetravex &tetravex_;
        int k_max_;

        std::vector<int> indices_map_;

        std::default_random_engine random_engine_;
        std::uniform_int_distribution<int> distribution_;

        float temperature(float frac);
        std::pair<int, int> random_permutation();
        void generate_map();
        static void apply_permutation(Tetravex& tetravex, const std::pair<int, int> &permutation);
        static float acceptance_probability(int cost, int new_cost, float temp);
    public:
        static int compute_cost(Tetravex& tetravex, const std::pair<int, int> &permutation);
        static int compute_cost(const Tetravex& tetravex);

        static bool is_solved(const Tetravex& tetravex);

        void solve();
        void solve_full_random();

        explicit Solver(Tetravex &tetravex, int k_max, int seed=-1);
    };
}


#endif //TETRAVEX_SOLVER_SOLVER_HH
