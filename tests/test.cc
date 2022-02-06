#include "generate.hh"
#include "../solver.hh"
#include "../io.hh"

#include <gtest/gtest.h>

TEST(Test_equality_op, Test_equals)
{
    using namespace tetrasolver;
    auto tetravex = tetravex_from_file("../test_files/given.txt");
    auto tetravex2 = tetravex_from_file("../test_files/given.txt");
    EXPECT_TRUE(tetravex == tetravex2);
}

TEST(Test_equality_op, Test_different)
{
    using namespace tetrasolver;
    auto tetravex = tetravex_from_file("../test_files/given.txt");
    auto tetravex2 = tetravex_from_file("../test_files/given.txt");
    tetravex2.board[0][1] = tetravex2.board[0][1] + 1;
    EXPECT_FALSE(tetravex == tetravex2);
}

TEST(Tests_solve_file, Solve_given_2x2) {
    using namespace tetrasolver;
    auto tetravex = tetravex_from_file("../test_files/given.txt");
    auto solver = Solver(tetravex, 10000000, 42);
    solver.solve();
    EXPECT_TRUE(solver.is_solved(tetravex));
    EXPECT_TRUE(tetravex == tetravex_from_file("../test_files/given-ref.txt"));
}

TEST(Tests_solve_file, Solve_txt_2x2) {
    using namespace tetrasolver;
    auto tetravex = tetravex_from_file("../test_files/bourquelot2.txt");
    auto solver = Solver(tetravex, 10000000, 42);
    solver.solve();
    EXPECT_TRUE(solver.is_solved(tetravex));
    EXPECT_TRUE(tetravex == tetravex_from_file("../test_files/bourquelot2-ref.txt"));
}
TEST(Tests_solve_file, Solve_txt_3x3) {
    using namespace tetrasolver;
    auto tetravex = tetravex_from_file("../test_files/bourquelot3.txt");
    auto solver = Solver(tetravex, 10000000, 42);
    solver.solve();
    EXPECT_TRUE(solver.is_solved(tetravex));
    EXPECT_TRUE(tetravex == tetravex_from_file("../test_files/bourquelot3-ref.txt"));
}
TEST(Tests_solve_file, Solve_txt_4x4) {
    using namespace tetrasolver;
    auto tetravex = tetravex_from_file("../test_files/bourquelot4.txt");
    auto solver = Solver(tetravex, 10000000, 42);
    solver.solve();
    EXPECT_TRUE(solver.is_solved(tetravex));
    EXPECT_TRUE(tetravex == tetravex_from_file("../test_files/bourquelot4-ref.txt"));
}
TEST(Tests_solve_file, Solve_txt_5x5) {
    using namespace tetrasolver;
    auto tetravex = tetravex_from_file("../test_files/bourquelot5.txt");
    auto solver = Solver(tetravex, 10000000, 42);
    solver.solve();
    EXPECT_TRUE(solver.is_solved(tetravex));
    EXPECT_TRUE(tetravex == tetravex_from_file("../test_files/bourquelot5-ref.txt"));
}

TEST(Tests_solve_file, Solve_txt_6x6) {
    using namespace tetrasolver;
    auto tetravex = tetravex_from_file("../test_files/bourquelot6.txt");
    auto solver = Solver(tetravex, 10000000, 42);
    solver.solve();
    EXPECT_TRUE(solver.is_solved(tetravex));
    EXPECT_TRUE(tetravex == tetravex_from_file("../test_files/bourquelot6-ref.txt"));
}


TEST(Tests_gen, Generation) {
    using namespace tetrasolver;

    for (int size = 2; size < 10; size++) {
        for (int seed = 0; seed < 100; seed++) {
            auto tetravex = generate_tetravex(size, seed, false);

            bool solved = Solver::is_solved(tetravex);
            int cost = Solver::compute_cost(tetravex);
            EXPECT_TRUE(solved);
            EXPECT_TRUE(cost == 0);
        }
    }
}

TEST(Tests_gen, Generation_shuffle) {
    using namespace tetrasolver;

    for (int size = 2; size < 10; size++) {
        for (int seed = 0; seed < 100; seed++) {
            auto tetravex = generate_tetravex(size, seed, true);

            bool solved = Solver::is_solved(tetravex);
            int cost = Solver::compute_cost(tetravex);
            EXPECT_FALSE(solved);
            EXPECT_FALSE(cost == 0);
        }
    }
}

int k_max = 1;

TEST(Tests_solve_s, Solve_2x2_already_solved) {
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(2, 420, false);

    auto solver = Solver(tetravex, k_max);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}

TEST(Tests_solve_s, Solve_3x3_already_solved) {
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(3, 420, false);

    auto solver = Solver(tetravex, k_max);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}

TEST(Tests_solve_s, Solve_4x4_already_solved) {
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(4, 420, false);

    auto solver = Solver(tetravex, k_max);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}

TEST(Tests_solve_s, Solve_5x5_already_solved) {
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(5, 420, false);

    auto solver = Solver(tetravex, k_max);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}

TEST(Tests_solve_s, Solve_6x6_already_solved) {
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(6, 420, false);

    auto solver = Solver(tetravex, k_max);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}

int k_max_s = 10000000;
int seed = 100;

TEST(Tests_solve, Solve_2x2) {
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(2, 420, true);

    auto solver = Solver(tetravex, k_max_s, seed);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}


TEST(Tests_solve, Solve_3x3) {
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(3, 420, true);

    auto solver = Solver(tetravex, k_max_s, seed);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}


TEST(Tests_solve, Solve_4x4) {
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(4, 420, true);

    auto solver = Solver(tetravex, k_max_s, seed);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}


TEST(Tests_solve, Solve_5x5) {
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(5, 420, true);

    auto solver = Solver(tetravex, k_max_s, seed);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}


TEST(Tests_solve, Solve_6x6) {
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(6, 428990, true);

    auto solver = Solver(tetravex, k_max_s, seed);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}

TEST(Tests_solve_random, Solve_2x2_random) {
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(2, 420, true);

    auto solver = Solver(tetravex, k_max_s);
    solver.solve_full_random();

    EXPECT_TRUE(!Solver::is_solved(tetravex));
}


TEST(Tests_solve_random, Solve_3x3_random) {
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(3, 420, true);

    auto solver = Solver(tetravex, k_max_s);
    solver.solve_full_random();

    EXPECT_TRUE(!Solver::is_solved(tetravex));
}


TEST(Tests_solve_random, Solve_4x4_random) {
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(4, 420, true);

    auto solver = Solver(tetravex, k_max_s);
    solver.solve_full_random();

    EXPECT_TRUE(!Solver::is_solved(tetravex));
}


TEST(Tests_solve_random, Solve_5x5_random) {
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(5, 420, true);

    auto solver = Solver(tetravex, k_max_s);
    solver.solve_full_random();

    EXPECT_TRUE(!Solver::is_solved(tetravex));
}


TEST(Tests_solve_random, Solve_6x6_random) {
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(6, 420, true);

    auto solver = Solver(tetravex, k_max_s);
    solver.solve_full_random();

    EXPECT_TRUE(!Solver::is_solved(tetravex));
}