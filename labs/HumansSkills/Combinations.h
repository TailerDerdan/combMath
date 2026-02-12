#pragma once

#include <vector>
#include <numeric>
#include <optional>
#include <set>
#include <algorithm>

using PeopleSkills = std::vector<std::set<size_t>>;

struct TeamFormationProblem
{
	PeopleSkills peopleSkills;
	std::set<size_t> requiredSkills;
};

bool NextCombinations(size_t dim, std::vector<size_t>& state)
{
	size_t iter = state.size() - 1;
	size_t maxDimInIter = dim;
	if (state[iter] < maxDimInIter)
	{
		state[iter]++;
		return true;
	}
	while (iter >= 0 && iter < state.size())
	{
		if (state[iter] < maxDimInIter)
		{
			break;
		}
		iter--;
		maxDimInIter--;
	}
	if (iter > state.size()) return false;

	state[iter]++;
	iter++;
	while (iter < state.size())
	{
		state[iter] = state[iter - 1] + 1;
		iter++;
	}
	return true;
}

bool IsGroupSuitable(std::vector<size_t> group, const TeamFormationProblem& teamFormationProblem)
{
	std::set<size_t> sumOfSkills;
	for (auto iter : group)
	{
		sumOfSkills.insert(teamFormationProblem.peopleSkills[iter - 1].begin(), 
			teamFormationProblem.peopleSkills[iter - 1].end());
	}
	if (std::includes(sumOfSkills.begin(), sumOfSkills.end(), 
		teamFormationProblem.requiredSkills.begin(), teamFormationProblem.requiredSkills.end()))
	{
		return true;
	}
	return false;
}

std::optional<std::vector<size_t>> GetGroupPeople(const TeamFormationProblem& teamFormationProblem)
{
	size_t dim = teamFormationProblem.peopleSkills.size();
	std::vector<size_t> group(dim);

	std::iota(group.begin(), group.end(), 1);
	if (!IsGroupSuitable(group, teamFormationProblem))
	{
		return std::nullopt;
	}
	group.clear();
	size_t iter = 1;
	group.push_back(iter);

	while (group.size() <= dim)
	{
		do 
		{
			if (IsGroupSuitable(group, teamFormationProblem))
			{
				return group;
			}
		} while (NextCombinations(dim, group));

		iter++;
		group.clear();
		for (size_t i = 1; i <= iter; ++i)
		{
			group.push_back(i);
		}
	}
	return std::nullopt;
}