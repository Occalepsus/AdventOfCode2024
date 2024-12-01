#include "Day1.h"

#include <iostream>
#include <algorithm>
#include <map>
#include "Utilities.h"

Day1::Day1()
{
	std::vector<std::string> lInput = Utilities::getFileLines("input/Day1.txt");

	mLList.reserve(lInput.size());
	mRList.reserve(lInput.size());

	for	(std::string const& lLine : lInput)
	{
		mLList.emplace_back(std::stoi(lLine.substr(0, 5)));
		mRList.emplace_back(std::stoi(lLine.substr(8, 5)));
	}
}

size_t Day1::part1()
{
	std::sort(mLList.begin(), mLList.end());
	std::sort(mRList.begin(), mRList.end());

	size_t res{ 0 };

	auto lLIt{ mLList.begin() };
	auto lRIt{ mRList.begin() };

	while (lLIt != mLList.end())
	{
		res += static_cast<size_t>(std::abs(*lLIt - *lRIt));

		lLIt++;
		lRIt++;
	}

	return res;
}

size_t Day1::part2()
{
	std::map<size_t, size_t> lCount{};
	for (int lVal : mRList)
	{
		lCount[lVal]++;
	}
	
	size_t res{ 0 };

	for (int lVal : mLList)
	{
		res += lVal * lCount[lVal];
	}

	return res;
}