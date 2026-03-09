#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include "../ArticulationPoint/Graph.h"

TEST_CASE("graph from lecture")
{
    Graph graph{};
    std::ifstream input;
    input.open("lectureTest.txt");
    graph.MakeGraphFromAdjMatrix(input);
    auto articulationPoint = graph.GetArticulationPoint();
    std::set<size_t> result = {0, 1, 2, 3, 6, 8};
    REQUIRE(articulationPoint == result);
}

TEST_CASE("graph from full graph")
{
    Graph graph{};
    std::ifstream input;
    input.open("fullGraph.txt");
    graph.MakeGraphFromAdjMatrix(input);
    auto articulationPoint = graph.GetArticulationPoint();
    std::set<size_t> result = {0};
    REQUIRE(articulationPoint == result);
}

TEST_CASE("graph from full two ways graph")
{
    Graph graph{};
    std::ifstream input;
    input.open("fullTwoWaysGraph.txt");
    graph.MakeGraphFromAdjMatrix(input);
    auto articulationPoint = graph.GetArticulationPoint();
    std::set<size_t> result = {0};
    REQUIRE(articulationPoint == result);
}

TEST_CASE("graph from tree")
{
    Graph graph{};
    std::ifstream input;
    input.open("tree.txt");
    graph.MakeGraphFromAdjMatrix(input);
    auto articulationPoint = graph.GetArticulationPoint();
    std::set<size_t> result = {0, 1, 2};
    REQUIRE(articulationPoint == result);
}

TEST_CASE("graph from circe")
{
    Graph graph{};
    std::ifstream input;
    input.open("circle.txt");
    graph.MakeGraphFromAdjMatrix(input);
    auto articulationPoint = graph.GetArticulationPoint();
    std::set<size_t> result = {0};
    REQUIRE(articulationPoint == result);
}
