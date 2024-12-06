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

	//for (std::list<int> const& lList : mData)
	//{
	//	auto lErrIt{ checkErr(lListCpy) };
	//	if (lErrIt == lListCpy.end())
	//	{
	//		res++;
	//	}
	//	else
	//	{



	//		int lFstElt{ lListCpy.front() };
	//		lListCpy.erase(lListCpy.begin());

	//		if (checkErr(lListCpy) == lListCpy.end())
	//		{
	//			res++;
	//			continue;
	//		}

	//		lListCpy.erase(lErrIt);
	//		lListCpy.push_front(lFstElt);
	//		if (checkErr(lListCpy) == lListCpy.end())
	//		{
	//			res++;
	//		}
	//	}
	//}

	return res;
}

std::list<int>::const_iterator Day2::checkErr(std::list<int> const& lList) const
{
	int lDiff{ 0 };

	auto lIt{ lList.begin() };
	auto lNextIt{ lList.begin() };
	lNextIt++;
	while (lNextIt != lList.end())
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

	return lList.end();
}
