#include <string>
#include <chrono>
#include <iostream>
#include <fstream>

#include "Graph.h"

int main()
{
    std::ifstream inputFile;
    std::ofstream outputFile;
    inputFile.open("./lectureTest.txt");
    outputFile.open("./output.txt");

    if (!inputFile.is_open() || !outputFile.is_open())
    {
        std::cout << "Could not open input file or output file\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();

    Graph graph;

    try
    {
        graph.MakeGraphFromListEdges(inputFile);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    graph.TransformListEdgesToAdjMatrix();
    // graph.PrintAdjMatrix(outputFile);
    auto articulationPoints = graph.GetArticulationPoint();

    auto end = std::chrono::high_resolution_clock::now();

    for (const auto& vertex : articulationPoints)
    {
        outputFile << vertex + 1 << std::endl;
    }

    std::chrono::duration<double> duration = end - start;
    std::cout << duration.count() << std::endl;

    outputFile.close();
    inputFile.close();
}