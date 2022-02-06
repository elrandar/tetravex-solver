#include "generate.hh"
#include "../solver.hh"

#include <gtest/gtest.h>

TEST(Tests_gen, Generation) {
    using namespace tetrasolver;

    for (int size = 2; size < 10; size++)
    {
        for (int seed = 0; seed < 100; seed++)
        {
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

    for (int size = 2; size < 10; size++)
    {
        for (int seed = 0; seed < 100; seed++)
        {
            auto tetravex = generate_tetravex(size, seed, true);

            bool solved = Solver::is_solved(tetravex);
            int cost = Solver::compute_cost(tetravex);
            EXPECT_FALSE(solved);
            EXPECT_FALSE(cost == 0);
        }
    }
}

int k_max = 1;

TEST(Tests_solve_s, Solve_2x2_already_solved)
{
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(2, 420, false);

    auto solver = Solver(tetravex, k_max);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}

TEST(Tests_solve_s, Solve_3x3_already_solved)
{
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(3, 420, false);

    auto solver = Solver(tetravex, k_max);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}

TEST(Tests_solve_s, Solve_4x4_already_solved)
{
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(4, 420, false);

    auto solver = Solver(tetravex, k_max);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}

TEST(Tests_solve_s, Solve_5x5_already_solved)
{
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(5, 420, false);

    auto solver = Solver(tetravex, k_max);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}
TEST(Tests_solve_s, Solve_6x6_already_solved)
{
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(6, 420, false);

    auto solver = Solver(tetravex, k_max);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}

int k_max_s = 10000000;
int seed = 51;

TEST(Tests_solve, Solve_2x2)
{
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(2, 420, true);

    auto solver = Solver(tetravex, k_max_s, seed);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}



TEST(Tests_solve, Solve_3x3)
{
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(3, 420, true);

    auto solver = Solver(tetravex, k_max_s, seed);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}



TEST(Tests_solve, Solve_4x4)
{
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(4, 420, true);

    auto solver = Solver(tetravex, k_max_s, seed);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}



TEST(Tests_solve, Solve_5x5)
{
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(5, 420, true);

    auto solver = Solver(tetravex, k_max_s, seed);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}


TEST(Tests_solve, Solve_6x6)
{
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(6, 428990, true);

    auto solver = Solver(tetravex, k_max_s, seed);
    solver.solve();

    EXPECT_TRUE(Solver::is_solved(tetravex));
}

TEST(Tests_solve_random, Solve_2x2_random)
{
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(2, 420, true);

    auto solver = Solver(tetravex, k_max_s);
    solver.solve_full_random();

    EXPECT_FALSE(Solver::is_solved(tetravex));
}



TEST(Tests_solve_random, Solve_3x3_random)
{
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(3, 420, true);

    auto solver = Solver(tetravex, k_max_s);
    solver.solve_full_random();

    EXPECT_FALSE(Solver::is_solved(tetravex));
}



TEST(Tests_solve_random, Solve_4x4_random)
{
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(4, 420, true);

    auto solver = Solver(tetravex, k_max_s);
    solver.solve_full_random();

    EXPECT_FALSE(Solver::is_solved(tetravex));
}



TEST(Tests_solve_random, Solve_5x5_random)
{
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(5, 420, true);

    auto solver = Solver(tetravex, k_max_s);
    solver.solve_full_random();

    EXPECT_FALSE(Solver::is_solved(tetravex));
}


TEST(Tests_solve_random, Solve_6x6_random)
{
    using namespace tetrasolver;

    auto tetravex = generate_tetravex(6, 420, true);

    auto solver = Solver(tetravex, k_max_s);
    solver.solve_full_random();

    EXPECT_TRUE(!Solver::is_solved(tetravex));
}
