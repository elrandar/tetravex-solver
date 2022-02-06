//
// Created by alexandre on 03/12/2021.
//
#include <iostream>
#include <chrono>
#include "solver.hh"
#include <cassert>

namespace tetrasolver
{

void Solver::solve(bool verbose) {
    int k = 0;
    float tmin = 0.6;
    float tmax = 1;
    float Tfactor = -log(tmax / tmin);

    int cost = compute_cost(tetravex_);
    int nb_tr = 0;
    while (k < k_max_) {
        float temp = temperature((float) k / (float) k_max_, Tfactor, tmax);

        auto permutation = random_permutation();
        int new_cost = compute_cost(tetravex_, permutation, cost);

        float r = distribution_f_(random_engine_);

        if (acceptance_probability(cost, new_cost, temp) > r) {
            apply_permutation(tetravex_, permutation);
            cost = new_cost;
            nb_tr++;
        }

        if (temp < tmax - 0.8 * (tmax - tmin))
            k = 0;

        if (cost == 0)
            break;
        k++;
    }

    if (verbose)
    {
        std::cout << (cost == 0 ? "Solved !" : "Not solved.") << std::endl;
        std::cout << "Current step : " << k << std::endl << "Current cost : " << cost << std::endl
            << "Number of transitions : " << nb_tr << std::endl;
    }
}

void Solver::solve_full_random(bool verbose) {
    int k = 0;

    int cost = compute_cost(tetravex_);
    while (k < k_max_) {
        auto permutation = random_permutation();
        int new_cost = compute_cost(tetravex_, permutation, cost);

        if (new_cost < cost) {
            apply_permutation(tetravex_, permutation);
            cost = new_cost;
        }
        if (cost < 0)
            break;
        k++;
    }

    if (verbose)
    {
        std::cout << (cost == 0 ? "Solved !" : "Not solved.") << std::endl;
        std::cout << "Current step : " << k << std::endl << "Current cost : " << cost << std::endl;
    }
}


bool Solver::is_solved(const Tetravex &tetravex) {
    int size = tetravex.size;

    const Tile *line_ptr = tetravex.board.data();
    const Tile *next_line_ptr = line_ptr + size;


    // Check all directions from the second line to the penultimate.
    for (int j = 0; j < size - 1; ++j)
    {
        // Check all the directions for all the lines expect for the last tile.
        for (int i = 0; i < size - 1; ++i)
        {
            if (line_ptr[i].right != line_ptr[i + 1].left)
                return false;

            if (line_ptr[i].down  != next_line_ptr[i].up)
                return false;
        }
        // Only check top-down for the last tile.
        if (line_ptr[size - 1].down != next_line_ptr[size - 1].up)
            return false;

        line_ptr += size;
        next_line_ptr += size;
    }

    // Check left-right for the last line.
    for (int i = 0; i < size - 1; ++i)
        if (line_ptr[i].right != line_ptr[i + 1].left)
            return false;

    return true;
}

Solver::Solver(tetrasolver::Tetravex &tetravex, int k_max, int seed)
        : tetravex_(tetravex),
          k_max_(k_max),
          distribution_f_(0, 1){
    if (seed == -1)
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    random_engine_.seed(seed);
    generate_map();
}

float Solver::temperature(float frac, float tratio, float tmax) {
    return tmax * exp(tratio * frac);
}

permutation Solver::random_permutation() {
    unsigned a = indices_map_[distribution_(random_engine_)];
    unsigned b = a;
    while (a == b) {
        b = indices_map_[distribution_(random_engine_)];
    }
    return {a, b};
}

void Solver::generate_map() {
    for (unsigned i = 0; i < tetravex_.is_frozen.size(); ++i)
        if (!tetravex_.is_frozen[i])
            indices_map_.push_back(i);
    distribution_ = std::uniform_int_distribution<int>(0, (int) indices_map_.size() - 1);
}

int Solver::compute_cost(Tetravex &tetravex, const permutation &permutation, int old_cost) {


    unsigned size = tetravex.size;

    const auto [j1, i1] = std::div(int(permutation.first), int(size));
    const auto [j2, i2] = std::div(int(permutation.second), int(size));

    const auto& board = tetravex.board;

// This should be a lambda, but since we can't use the optimasation flags, it
// won't be inline.
#define CHECK_TILE(i, j, idx, out_errors)                                   \
    {                                                                       \
        const Tile& tile = board[j*size + i];                               \
                                                                            \
        if (i > 0        && idx - 1 != permutation.first)                   \
            out_errors += (tile.left != board[idx - 1].right);              \
                                                                            \
        if (i < size - 1 && idx + 1 != permutation.first)                   \
            out_errors += (tile.right != board[idx + 1].left);              \
                                                                            \
        if (j > 0        && idx - size != permutation.first)                \
            out_errors += (tile.up != board[idx - size].down);              \
                                                                            \
        if (j < size - 1 && idx + size != permutation.first)                \
            out_errors += (tile.down != board[idx + size].up);              \
    }

    unsigned old_errors = 0;
    CHECK_TILE(i1, j1, permutation.first, old_errors);
    CHECK_TILE(i2, j2, permutation.second, old_errors);


    apply_permutation(tetravex, permutation);

    unsigned new_errors = 0;
    CHECK_TILE(i1, j1, permutation.first, new_errors);
    CHECK_TILE(i2, j2, permutation.second, new_errors);

    apply_permutation(tetravex, permutation);

    return old_cost - (old_errors - new_errors)*2;
}

int Solver::compute_cost(const Tetravex &tetravex) {
    unsigned nb_errors = 0;
    unsigned size = tetravex.size;

    const Tile *line_ptr = tetravex.board.data();
    const Tile *next_line_ptr = line_ptr + size;


    // Check all directions from the second line to the penultimate.
    for (unsigned j = 0; j < size - 1; ++j)
    {
        // Check all the directions for all the lines expect for the last tile.
        for (unsigned i = 0; i < size - 1; ++i)
        {
            nb_errors += (line_ptr[i].right != line_ptr[i + 1].left);
            nb_errors += (line_ptr[i].down  != next_line_ptr[i].up);
        }
        // Only check top-down for the last tile.
        nb_errors += (line_ptr[size - 1].down != next_line_ptr[size - 1].up);

        line_ptr += size;
        next_line_ptr += size;
    }

    // Check left-right for the last line.
    for (unsigned i = 0; i < size - 1; ++i)
        nb_errors += (line_ptr[i].right != line_ptr[i + 1].left);

    return nb_errors*2;
}


void Solver::apply_permutation(Tetravex &tetravex, const permutation &permutation) {
    std::swap(tetravex.board[permutation.first],
              tetravex.board[permutation.second]);
}

float Solver::acceptance_probability(int cost, int new_cost, float temp) {
    if (new_cost < cost)
        return 1;
    else {
        return std::exp(-(float) (new_cost - cost) / temp);
    }
}
}
