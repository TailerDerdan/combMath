#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>

using Num = long;

using matrix = std::vector<std::vector<Num>>;

void GetSumOfEdges(const matrix& mat, const std::vector<int>& setVertex)
{
    Num sum = 0;
    for (size_t iter = 1; iter < setVertex.size(); iter++)
    {
        sum += mat[iter][];
    }
}

int main()
{
    std::vector<int> v = { -6, -5, -4, -3, -2, -1, 0 };
    auto start = std::chrono::high_resolution_clock::now();

    

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << duration.count() << std::endl;
}