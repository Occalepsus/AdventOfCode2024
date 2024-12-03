#include "Day3.h"

#include <iostream>
#include "Utilities.h"
#include <regex>

Day3::Day3() : mData{ Utilities::getFileAsRaw("input/Day3.txt") }
{}

size_t Day3::part1()
{
	size_t lRes{ 0 };

	std::regex lRegex{ R"(mul\((\d+),(\d+)\))" };

	auto lMatchesBegin{ std::sregex_iterator(mData.cbegin(), mData.cend(), lRegex) };
	auto lMatchesEnd{ std::sregex_iterator() };

	for (std::sregex_iterator lIt{ lMatchesBegin }; lIt != lMatchesEnd; lIt++)
	{
		std::smatch lMatch = *lIt;
		std::cout << lMatch.str() << '\n';

		if (lMatch.size() == 3)
		{
			lRes += std::stoull(lMatch[1].str()) * std::stoull(lMatch[2].str());
		}
	}

	return lRes;
}

size_t Day3::part2()
{
	size_t lRes{ 0 };

	bool lEnabled{ true };

	std::regex lRegex{ R"((?:mul\((\d+),(\d+)\))|(?:do(?:n't)?\(\)))" };

	auto lMatchesBegin{ std::sregex_iterator(mData.cbegin(), mData.cend(), lRegex) };
	auto lMatchesEnd{ std::sregex_iterator() };

	for (std::sregex_iterator lIt{ lMatchesBegin }; lIt != lMatchesEnd; lIt++)
	{
		std::smatch lMatch = *lIt;
		std::cout << lMatch.str() << '\n';

		if (lMatch.length() == 4)
		{
			lEnabled = true;
		}
		else if (lMatch.length() == 7)
		{
			lEnabled = false;
		}

		else if (lEnabled && lMatch.size() == 3)
		{
			lRes += std::stoull(lMatch[1].str()) * std::stoull(lMatch[2].str());
		}
	}

	return lRes;
}