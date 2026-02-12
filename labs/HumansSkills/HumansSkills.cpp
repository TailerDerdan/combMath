#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <chrono>

#include "Combinations.h"

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
            << "Usage: humanskills.exe <inputFile> <outputFile>\n";
        return std::nullopt;
    }

    args.input = argv[1];
    args.output = argv[2];
    return args;
}

std::set<size_t> GetSetFromStr(const std::string& row)
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

    std::set<size_t> rowNums;
    for (auto token : tokens)
    {
        size_t num = std::stol(token);
        rowNums.insert(num);
    }
    return rowNums;
}

TeamFormationProblem GetDataFromFile(std::ifstream& input)
{
    std::string line;
    std::getline(input, line);

    TeamFormationProblem teamFormationProblem;
    teamFormationProblem.requiredSkills = GetSetFromStr(line);

    while (std::getline(input, line))
    {
        teamFormationProblem.peopleSkills.push_back(GetSetFromStr(line));
    }
    
    return teamFormationProblem;
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

    auto teamFormationProblem = GetDataFromFile(inputFile);

    auto start = std::chrono::high_resolution_clock::now();

    auto group = GetGroupPeople(teamFormationProblem);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << duration.count() << std::endl;

    if (group.has_value())
    {
        copy(group.value().begin(), group.value().end(), std::ostream_iterator<size_t>(outputFile, " "));
        return EXIT_SUCCESS;
    }

    outputFile << "it is impossible to assemble a group" << std::endl;
}