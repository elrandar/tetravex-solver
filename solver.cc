//
// Created by alexandre on 03/12/2021.
//
#include <iostream>
#include "solver.hh"


void tetrasolver::Solver::solve() {
    if (is_solved())
        std::cout << "Tetravex is solved\n";
    else
        std::cout << "Tetravex not solved\n";


    int k = 0;
    int cost = compute_cost(std::make_pair(0,0));
    while (k < k_max)
    {
        float temp = temperature((float) k / (float) k_max);
        auto permutation = random_permutation();
        int new_cost = compute_cost(permutation);

        float r = ((double) rand() / (RAND_MAX));
        if (acceptance_probability(cost, new_cost, temp) > r)
        {
            apply_permutation(permutation);
            cost = new_cost;
            if (cost == 0)
                break;
        }
        k++;
    }
    std::cout << "Current step : " << k << std::endl << "Current cost : " << cost << std::endl;
}

bool tetrasolver::Solver::is_solved() const {
    for (int i = 0; i < tetravex.board.size(); i++) {
        auto board = tetravex.board;
        if (i % tetravex.size != tetravex.size - 1 && board[i].right != board[i + 1].left) // right
            return false;
        if (i % tetravex.size > 0 && board[i].left != board[i - 1].right) // left
            return false;
        if (i + tetravex.size < tetravex.board.size() && board[i].down != board[i + tetravex.size].up)
            return false;
        if (i - (int)tetravex.size >= 0 && board[i].up != board[i - (int)tetravex.size].down)
            return false;
    }
    return true;
}

tetrasolver::Solver::Solver(tetrasolver::Tetravex &tetravex, int k_max)
        : tetravex(tetravex),
          k_max(k_max){
    random_engine.seed(42);
    generate_map();
}

float tetrasolver::Solver::temperature(float frac) {
    return std::max(0.01f, std::min(1.0f, 1.0f - frac));
}

std::pair<int, int> tetrasolver::Solver::random_permutation() {
    auto a = 0;
    auto b = 0;
    while (a == b) {
        a = indices_map[distribution(random_engine)];
        b = indices_map[distribution(random_engine)];
    }
    return std::make_pair(a, b);
}

void tetrasolver::Solver::generate_map() {
    int i = 0;
    for (auto tile : tetravex.board)
    {
        if (!tile.frozen)
            indices_map.push_back(i);
        i++;
    }
    distribution = std::uniform_int_distribution(0, (int)indices_map.size() - 1);
}

int tetrasolver::Solver::compute_cost(const std::pair<int, int> &permutation) {
    apply_permutation(permutation);
    int nb_errors = 0;
    for (int i = 0; i < tetravex.board.size(); i++) {
        auto board = tetravex.board;
        if (i % tetravex.size != tetravex.size - 1 && board[i].right != board[i + 1].left) // right
            nb_errors++;
        if (i % tetravex.size != 0 && board[i].left != board[i - 1].right) // left
            nb_errors++;
        if (i + tetravex.size < tetravex.board.size() && board[i].down != board[i + tetravex.size].up)
            nb_errors++;
        if (i - (int)tetravex.size >= 0 && board[i].up != board[i - (int)tetravex.size].down)
            nb_errors++;
    }
    apply_permutation(permutation);
    return nb_errors;
}

void tetrasolver::Solver::apply_permutation(const std::pair<int, int> &permutation) {
    if (permutation.first != permutation.second) {
        auto tmp = tetravex.board[permutation.first];
        tetravex.board[permutation.first] = tetravex.board[permutation.second];
        tetravex.board[permutation.second] = tmp;
    }
}

float tetrasolver::Solver::acceptance_probability(int cost, int new_cost, float temp) {
    if (new_cost < cost)
        return 1;
    else
    {
        auto p = std::exp(- (float)(new_cost - cost) / temp);
        return p;
    }
}
