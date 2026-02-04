#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../Salesman/SalesMan.h"

TEST_CASE("Check for matrix 3x3")
{
    matrix mat = {
        {0, 446, 140},
        {446, 0, 8},
        {140, 8, 0}
    };
    auto path = GetShortestPath(mat);
    std::vector<size_t> answer = {0, 1, 2};
    CHECK(path == answer);
}

TEST_CASE("Check for matrix 4x4")
{
    matrix mat = {
        {0, 282, 334, 61},
        {282, 0, 39, 81},
        {334, 39, 0, 147},
        {61, 81, 147, 0}
    };
    auto path = GetShortestPath(mat);
    std::vector<size_t> answer = { 0, 2, 1, 3 };
    CHECK(path == answer);
}

TEST_CASE("Check for matrix 4x4 with negative numbers")
{
    matrix mat = {
        {0, -282, -334, -61},
        {-282, 0, -39, -81},
        {-334, -39, 0, -147},
        {-61, -81, -147, 0}
    };
    auto path = GetShortestPath(mat);
    std::vector<size_t> answer = { 0, 1, 3, 2 };
    CHECK(path == answer);
}