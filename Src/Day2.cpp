#include "Day2.h"

#include <iostream>
#include "Utilities.h"

Day2::Day2()
{
	std::vector<std::string> lInput = Utilities::getFileLines("input/Day2.txt");
	mData.reserve(lInput.size());
	
	for (auto const& lLine : lInput)
	{
		mData.emplace_back();
		std::list<int>& lLineData{ mData.back() };

		size_t lLinePos{ 0 };
		while (lLinePos < lLine.size())
		{
			size_t lNextPos{ lLine.find(' ', lLinePos + 1) };

			lLineData.push_back(std::stoi(lLine.substr(lLinePos, lNextPos)));
			lLinePos = lNextPos;
		}
	}
}

size_t Day2::part1()
{
	size_t res{ 0 };

	for (auto const& lLine : mData)
	{
		auto lErrIt{ checkErr(lLine) };
		if (lErrIt == lLine.end())
		{
			res++;
		}
	}

	return res;
}

size_t Day2::part2()
{
	size_t res{ 0 };

	for (std::list<int> const& lList : mData)
	{
		if (checkErr(lList) == lList.end())
		{
			res++;
			continue;
		}

		std::list<int> lListIncr_cpy{ lList };
		if (auto lIncrErrIt{ checkErrOrdered(lListIncr_cpy, true) }; lIncrErrIt != lListIncr_cpy.end())
		{
			int lVal{ *lIncrErrIt };
			auto lIt{ lListIncr_cpy.erase(lIncrErrIt) };

			if (checkErr(lListIncr_cpy) == lListIncr_cpy.end())
			{
				res++;
				continue;
			}

			lListIncr_cpy.insert(lIt, lVal);
			
			lIt = lListIncr_cpy.erase(lIt);

			if (checkErr(lListIncr_cpy) == lListIncr_cpy.end())
			{
				res++;
				continue;
			}
		}

		std::list<int> lListDecr_cpy{ lList };
		if (auto lDecrErrIt{ checkErrOrdered(lListDecr_cpy, false) }; lDecrErrIt != lListDecr_cpy.end())
		{
			int lVal{ *lDecrErrIt };
			auto lIt{ lListDecr_cpy.erase(lDecrErrIt) };

			if (checkErr(lListDecr_cpy) == lListDecr_cpy.end())
			{
				res++;
				continue;
			}

			lListDecr_cpy.insert(lIt, lVal);

			lIt = lListDecr_cpy.erase(lIt);

			if (checkErr(lListDecr_cpy) == lListDecr_cpy.end())
			{
				res++;
				continue;
			}
		}

		for (int lVal : lList)
		{
			std::cout << lVal << " ";
		}
		std::cout << "\n";
	}

	return res;
}

std::list<int>::const_iterator Day2::checkErr(std::list<int> const& pList) const
{
	int lDiff{ 0 };

	auto lIt{ pList.begin() };
	auto lNextIt{ pList.begin() };
	lNextIt++;
	while (lNextIt != pList.end())
	{
		int lNewDiff{ *lNextIt - *lIt };

		if (std::abs(lNewDiff) > 3 || lNewDiff == 0 || lDiff * lNewDiff < 0)
		{
			return lIt;
		}
		lDiff = lNewDiff;
		lIt++;
		lNextIt++;
	}

	return pList.end();
}

std::list<int>::const_iterator Day2::checkErrOrdered(std::list<int> const& pList, bool pIncr) const
{
	int lDiff{ 0 };

	auto lIt{ pList.begin() };
	auto lNextIt{ pList.begin() };
	lNextIt++;
	while (lNextIt != pList.end())
	{
		lDiff = *lNextIt - *lIt;

		if (std::abs(lDiff) > 3 || lDiff == 0 || (pIncr && lDiff > 0) || (!pIncr && lDiff < 0))
		{
			return lIt;
		}
		lIt++;
		lNextIt++;
	}

	return pList.end();
}

/*
	-> 647 wrong
	-> 658 ???
*/