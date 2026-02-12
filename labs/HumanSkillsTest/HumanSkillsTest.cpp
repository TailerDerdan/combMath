#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../HumansSkills/Combinations.h"

TEST_CASE("Get next after max")
{
    std::vector<size_t> state = { 7, 8, 9, 10 };
    size_t dim = 10;

    auto isNextComb = NextCombinations(dim, state);
    std::vector<size_t> result = { 7, 8, 9, 10 };

    CHECK(isNextComb == false);
    CHECK(state == result);
}

TEST_CASE("Get next combination")
{
    std::vector<size_t> state = { 1, 3, 9, 10 };
    size_t dim = 10;

    auto isNextComb = NextCombinations(dim, state);
    std::vector<size_t> result = { 1, 4, 5, 6 };

    CHECK(isNextComb == true);
    CHECK(state == result);
}

TEST_CASE("Get next combination from wrong state")
{
    std::vector<size_t> state = { 1, 9, 9, 10 };
    size_t dim = 10;

    auto isNextComb = NextCombinations(dim, state);
    std::vector<size_t> result = { 2, 3, 4, 5 };

    CHECK(isNextComb == true);
    CHECK(state == result);
}

TEST_CASE("Check group with redundant data")
{
    TeamFormationProblem teamFormationProblem;
    teamFormationProblem.requiredSkills = {1, 3, 5, 8};

    teamFormationProblem.peopleSkills = {
        {1, 2, 3, 4, 5},
        {6, 7, 8, 11, 14},
        {8, 10},
        {1, 3, 8},
        {10},
        {11},
    };

    auto group = GetGroupPeople(teamFormationProblem);
    REQUIRE(group.has_value());
    CHECK(group.value() == std::vector<size_t>{1, 2});
}

TEST_CASE("Single person covers all required skills")
{
    TeamFormationProblem teamFormationProblem;
    teamFormationProblem.requiredSkills = { 2, 5, 7 };

    teamFormationProblem.peopleSkills = {
        {1, 3, 4},
        {2, 5, 7, 9},
        {1, 2, 3},
    };

    auto group = GetGroupPeople(teamFormationProblem);
    REQUIRE(group.has_value());
    CHECK(group.value() == std::vector<size_t>{2});
}

TEST_CASE("Each person has exactly one unique required skill")
{
    TeamFormationProblem teamFormationProblem;
    teamFormationProblem.requiredSkills = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    teamFormationProblem.peopleSkills = {
        {1},
        {2},
        {3},
        {4},
        {5},
        {6},
        {7},
        {8},
        {9},
        {10},
    };

    auto group = GetGroupPeople(teamFormationProblem);
    REQUIRE(group.has_value());
    CHECK(group.value() == std::vector<size_t>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
}

TEST_CASE("No solution exists")
{
    TeamFormationProblem teamFormationProblem;
    teamFormationProblem.requiredSkills = { 1, 2, 3, 99 };

    teamFormationProblem.peopleSkills = {
        {1, 2},
        {2, 3},
        {1, 3},
    };

    auto group = GetGroupPeople(teamFormationProblem);
    CHECK_FALSE(group.has_value());
}