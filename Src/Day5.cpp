#include "Day5.h"

#include <iostream>
#include "Utilities.h"

Day5::Day5()
{
	std::vector<std::string> lInput{ Utilities::getFileLines("input/Day5.txt") };

	bool lLists{ false };
	for (const auto& lLine : lInput)
	{
		if (!lLists)
		{
			if (lLine.empty())
			{
				lLists = true;
				continue;
			}

			size_t lSplit{ lLine.find('|') };

			size_t lPage{ std::stoull(lLine.substr(0, lSplit)) };
			size_t lNextPage{ std::stoull(lLine.substr(lSplit + 1)) };

			mPagesOrdering[lPage].insert(lNextPage);
		}
		else
		{
			mPagesLists.emplace_back();
			auto& lPagesList{ mPagesLists.back() };
			
			size_t lPos{ 0 };
			while (lPos < lLine.size())
			{
				size_t lNextPos{ lLine.find(',', lPos) };
				lNextPos = lNextPos == std::string::npos ? lLine.size() : lNextPos;

				lPagesList.push_back(std::stoull(lLine.substr(lPos, lNextPos - lPos)));

				lPos = lNextPos + 1;
			}
		}
	}
}

size_t Day5::part1()
{
	size_t lRes{ 0 };

	for (const auto& lPagesList : mPagesLists)
	{
		if (isOrdered(lPagesList))
		{
			lRes += findMiddle(lPagesList);

			for (auto lVal : lPagesList)
			{
				std::cout << lVal << " ";
			}
			std::cout << "\n";
		}
	}

	return lRes;
}

size_t Day5::part2()
{
	size_t lRes{ 0 };

	for (auto& lPagesList : mPagesLists)
	{
		bool lOrderedBefore{ true };
		while (!isOrdered(lPagesList))
		{
			lOrderedBefore = false;

			reorderList(lPagesList);
		}
		if (!lOrderedBefore)
		{

			for (auto lVal : lPagesList)
			{
				std::cout << lVal << " ";
			}

			lRes += findMiddle(lPagesList);
			std::cout << " | " << lRes << "\n";
		}
		else
		{
			for (auto lVal : lPagesList)
			{
				std::cout << lVal << " ";
			}
			std::cout << "\n";
		}
	}

	return lRes;
}

size_t Day5::findMiddle(std::list<size_t> const& pList)
{
	auto lSlowIt = pList.begin();
	auto lFastIt = pList.begin();

	while (lFastIt != pList.end() && std::next(lFastIt) != pList.end()) {
		++lSlowIt;
		std::advance(lFastIt, 2);
	}

	return *lSlowIt;
}

bool Day5::isOrdered(std::list<size_t> const& pList) const
{
	bool lValid{ true };

	for (auto lIt{ pList.begin() }; std::next(lIt) != pList.end(); lIt++)
	{
		auto const& lNextPagesIt{ mPagesOrdering.find(*lIt) };

		if (lNextPagesIt == mPagesOrdering.end()
			|| lNextPagesIt->second.find(*std::next(lIt)) == lNextPagesIt->second.end())
		{
			lValid = false;
			break;
		}
	}

	return lValid;
}

void Day5::reorderList(std::list<size_t>& pList)
{
	auto lIt{ pList.begin() };

	while (std::next(lIt) != pList.end())
	{
		auto const& lNextPagesIt{ mPagesOrdering.find(*lIt) };

		if (lNextPagesIt == mPagesOrdering.end()
			|| lNextPagesIt->second.find(*std::next(lIt)) == lNextPagesIt->second.end())
		{
			size_t lVal{ *lIt };
			auto lNewIt{ pList.erase(lIt) };

			pList.insert(std::next(lNewIt), lVal);
			lIt = lNewIt;
		}
		else
		{
			lIt++;
		}
	}
}