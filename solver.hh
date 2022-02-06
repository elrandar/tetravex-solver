//
// Created by alexandre on 03/12/2021.
//

#ifndef TETRAVEX_SOLVER_SOLVER_HH
#define TETRAVEX_SOLVER_SOLVER_HH

#include "tetravex.hh"
#include <random>


namespace tetrasolver {

    // Simpler std::pair since it can be slow especially when compilling without
    // optimisation flags.
    struct permutation
    {
        unsigned first, second;
    };
    class Solver {

        Tetravex &tetravex_;
        int k_max_;

        std::vector<int> indices_map_;

        std::ranlux24_base random_engine_;
        std::uniform_int_distribution<int> distribution_;
        std::uniform_real_distribution<float> distribution_f_;

        float temperature(float frac, float tratio, float tmax);
        permutation random_permutation();
        void generate_map();
        static void apply_permutation(Tetravex& tetravex, const permutation& permutation);
        static float acceptance_probability(int cost, int new_cost, float temp);
    public:
        static int compute_cost(Tetravex& tetravex, const permutation &permutation, int old_cost);
        static int compute_cost(const Tetravex& tetravex);

        static bool is_solved(const Tetravex& tetravex);

        void solve(bool verbose=false);
        void solve_full_random(bool verbose=false);

        explicit Solver(Tetravex &tetravex, int k_max, int seed=-1);
    };
}


#endif //TETRAVEX_SOLVER_SOLVER_HH
