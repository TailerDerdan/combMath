#include <iostream>
#include <chrono>
#include <optional>
#include <fstream>
#include <regex>

#include "SalesMan.h"

struct Args
{
    std::string input;
    std::string output;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	std::string input;
	std::string output;

	Args args;

	if (argc != 3)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: salesman.exe <inputFile> <outputFile>\n";
		return std::nullopt;
	}

	args.input = argv[1];
	args.output = argv[2];
	return args;
}

std::vector<Num> GetVectorFromStr(const std::string& row)
{
	std::regex exp(R"(\s+)");
	std::vector<std::string> tokens(
		std::sregex_token_iterator(row.begin(), row.end(), exp, -1),
		std::sregex_token_iterator()
	);

	tokens.erase(
		std::remove_if(tokens.begin(), tokens.end(),
			[](const std::string& s) { return s.empty(); }),
		tokens.end()
	);
	
	std::vector<Num> rowNums;
	for (auto token : tokens)
	{
		Num num = std::stol(token);
		rowNums.push_back(num);
	}
	return rowNums;
}

matrix GetMatrixFromFile(std::istream& inputFile)
{
	std::string row;
	matrix result;

	while (std::getline(inputFile, row))
	{
		result.push_back(GetVectorFromStr(row));
	}
	return result;
}

void PrintMatrix(std::ostream& out, const matrix& mat)
{
	for (size_t iterCol = 0; iterCol < mat.size(); iterCol++)
	{
		for (size_t iterRow = 0; iterRow < mat[iterCol].size(); iterRow++)
		{
			out << mat[iterCol][iterRow] << "	";
		}
		out << std::endl;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return EXIT_FAILURE;
	}

	std::ifstream inputFile;
	std::ofstream outputFile;
	inputFile.open(args.value().input);
	outputFile.open(args.value().output);

	auto matrix = GetMatrixFromFile(inputFile);

    auto start = std::chrono::high_resolution_clock::now();

	auto shortestPath = GetShortestPath(matrix);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << duration.count() << std::endl;

	copy(shortestPath.begin(), shortestPath.end(), std::ostream_iterator<size_t>(outputFile, " "));
	outputFile << std::endl << GetSumOfEdges(matrix, shortestPath);
}