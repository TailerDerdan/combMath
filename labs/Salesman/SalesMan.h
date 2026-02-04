#pragma once

#include <algorithm>
#include <vector>
#include <numeric>

using Num = long;

using matrix = std::vector<std::vector<Num>>;

Num GetSumOfEdges(const matrix& mat, const std::vector<size_t>& setVertex)
{
	Num sum = 0;
	for (size_t iter = 1; iter < setVertex.size(); iter++)
	{
		sum += mat[setVertex[iter - 1]][setVertex[iter]];
	}
	sum += mat[setVertex[setVertex.size() - 1]][setVertex[0]];
	return sum;
}

std::vector<size_t> GetShortestPath(const matrix& mat)
{
	std::vector<size_t> setOfVertex(mat.size());
	std::iota(setOfVertex.begin(), setOfVertex.end(), size_t(0));

	size_t resultSum = SIZE_MAX;
	size_t curSum = 0;
	std::vector<size_t> vertexShortestPath;

	do
	{
		curSum = GetSumOfEdges(mat, setOfVertex);
		if (curSum < resultSum)
		{
			resultSum = curSum;
			vertexShortestPath = setOfVertex;
		}

	} while (std::next_permutation(setOfVertex.begin(), setOfVertex.end()));

	return vertexShortestPath;
}