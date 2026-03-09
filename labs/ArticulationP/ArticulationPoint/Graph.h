#pragma once

#include <set>
#include <vector>

struct Edge
{
    int weight;
    size_t uVertex;
    size_t vVertex;
};

struct TimePoint
{
    size_t start;
    size_t end;
};

using AdjMatrix = std::vector<std::vector<int>>;
using AdjList = std::vector<std::vector<size_t>>;
using ListEdges = std::vector<Edge>;

class Graph
{
public:
    Graph();
    ~Graph() = default;

    void MakeGraphFromAdjMatrix(std::istream& input);
    void MakeGraphFromListEdges(std::istream& input);

    void TransformAdjMatrixToListEdges();
    void TransformListEdgesToAdjMatrix();

    void PrintAdjMatrix(std::ostream& output) const;
    void PrintEdges(std::ostream& output) const;

    std::set<size_t> GetArticulationPoint();

private:
    [[nodiscard]] AdjList TransformAdjMatrixToAdjList() const;

    static std::vector<int> GetVectorFromStr(const std::string& row);
    static Edge GetEdgeFromStr(const std::string& row);

private:
    ListEdges edges;
    AdjMatrix adjMatrix;
};