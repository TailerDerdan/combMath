#include "Graph.h"

#include <regex>
#include <string>
#include <fstream>
#include <iostream>

Graph::Graph() = default;

void Graph::MakeGraphFromAdjMatrix(std::istream& input)
{
    std::string row;

    while (std::getline(input, row))
    {
        adjMatrix.push_back(GetVectorFromStr(row));
    }
    if (adjMatrix.size() != adjMatrix[0].size())
    {
        throw std::logic_error("Wrong number of vertices");
    }
}

std::vector<int> Graph::GetVectorFromStr(const std::string& row)
{
    const std::regex exp(R"(\s+)");
    std::vector<std::string> tokens(
        std::sregex_token_iterator(row.begin(), row.end(), exp, -1),
        std::sregex_token_iterator()
    );

    std::erase_if(tokens,
                  [](const std::string& s) { return s.empty(); });

    std::vector<int> rowNums;
    for (const auto& token : tokens)
    {
        int num = std::stoi(token);
        rowNums.push_back(num);
    }
    return rowNums;
}

void Graph::MakeGraphFromListEdges(std::istream& input)
{
    std::string row;

    while (std::getline(input, row))
    {
        edges.push_back(GetEdgeFromStr(row));
    }
}

Edge Graph::GetEdgeFromStr(const std::string& row)
{
    const std::regex exp(R"(\s+)");
    std::vector<std::string> tokens(
        std::sregex_token_iterator(row.begin(), row.end(), exp, -1),
        std::sregex_token_iterator()
    );

    std::erase_if(tokens,
                  [](const std::string& s) { return s.empty(); });

    if (tokens.size() != 2 && tokens.size() != 3)
    {
        throw std::logic_error("Wrong number of edge");
    }

    Edge edge{};
    edge.uVertex = std::stoi(tokens[0]) - 1;
    edge.vVertex = std::stoi(tokens[1]) - 1;
    edge.weight = 0;

    if (tokens.size() == 3)
    {
        edge.weight = std::stoi(tokens[2]);
    }

    return edge;
}

void Graph::TransformAdjMatrixToListEdges()
{
    edges.clear();
    for (size_t row = 0; row < adjMatrix.size(); row++)
    {
        for (size_t col = row + 1; col < adjMatrix.size(); col++)
        {
            if (adjMatrix[row][col])
            {
                Edge edge{};
                edge.uVertex = row;
                edge.vVertex = col;
                edge.weight = adjMatrix[row][col] == 1 ? 0 : adjMatrix[row][col];
                edges.push_back(edge);
            }
        }
    }
}

void Graph::TransformListEdgesToAdjMatrix()
{
    adjMatrix.clear();

    size_t maxVertex = 0;
    for (const auto& edge : edges)
        maxVertex = std::max({maxVertex, edge.uVertex, edge.vVertex});

    adjMatrix.assign(maxVertex + 1, std::vector<int>(maxVertex + 1, 0));

    for (const auto&[weight, uVertex, vVertex] : edges)
    {
        adjMatrix[uVertex][vVertex] = weight ? weight : 1;
        adjMatrix[vVertex][uVertex] = weight ? weight : 1;
    }
}

AdjList Graph::TransformAdjMatrixToAdjList() const
{
    AdjList adjList(adjMatrix.size());
    for (size_t row = 0; row < adjMatrix.size(); row++)
    {
        for (size_t col = row + 1; col < adjMatrix.size(); col++)
        {
            if (adjMatrix[row][col])
            {
                adjList[row].push_back(col);
                adjList[col].push_back(row);
            }
        }
    }
    return adjList;
}

std::set<size_t> Graph::GetArticulationPoint()
{
    if (adjMatrix.empty())
    {
        TransformListEdgesToAdjMatrix();
    }

    std::vector<TimePoint> timePoints;
    constexpr size_t UNVISITED_VALUE = 0;
    for (size_t col = 0; col < adjMatrix.size(); col++)
    {
        TimePoint timePoint{};
        timePoint.start = UNVISITED_VALUE;
        timePoint.end = UNVISITED_VALUE;
        timePoints.push_back(timePoint);
    }

    std::vector<size_t> up(adjMatrix.size(), INT_MAX);
    const auto adjList = TransformAdjMatrixToAdjList();
    std::vector<size_t> parent(adjList.size(), -1);
    std::stack<size_t> stack;

    stack.push(0);
    int timePoint = 0;

    size_t rootChildrenCount = 0;
    std::set<size_t> articulationPoints;

    while (!stack.empty())
    {
        if (timePoints[stack.top()].start == UNVISITED_VALUE)
        {
            timePoint++;
            timePoints[stack.top()].start = timePoint;
            up[stack.top()] = timePoint;
        }
        const size_t lastVertex = stack.top();
        for (size_t neighbor : adjList[lastVertex])
        {
            if (timePoints[neighbor].start == UNVISITED_VALUE)
            {
                parent[neighbor] = lastVertex;
                if (lastVertex == 0) rootChildrenCount++;
                stack.push(neighbor);
            }
            else if (neighbor != parent[lastVertex])
            {
                up[lastVertex] = std::min(up[lastVertex], timePoints[neighbor].start);
            }
        }
        if (lastVertex == stack.top())
        {
            if (timePoints[lastVertex].end == UNVISITED_VALUE)
            {
                timePoint++;
                timePoints[lastVertex].end = timePoint;
            }
            if (parent[lastVertex] != -1)
            {
                up[parent[lastVertex]] = std::min(up[parent[lastVertex]], up[lastVertex]);

                if (up[lastVertex] >= timePoints[parent[lastVertex]].start)
                {
                    articulationPoints.insert(parent[lastVertex]);
                }
            }
            else
            {
                if (rootChildrenCount > 1)
                {
                    articulationPoints.insert(lastVertex);
                }
            }
            stack.pop();
        }
    }
    return articulationPoints;
}

void Graph::PrintAdjMatrix(std::ostream& output) const
{
    for (size_t row = 0; row < adjMatrix.size(); row++)
    {
        for (size_t col = 0; col < adjMatrix.size(); col++)
        {
            output << adjMatrix[row][col] << " ";
        }
        output << std::endl;
    }
}
void Graph::PrintEdges(std::ostream& output) const
{
    for (const auto&[weight, uVertex, vVertex] : edges)
    {
        output << uVertex + 1 << " " << vVertex + 1 << " " << weight << std::endl;
    }
}