#include "Day7.h"

#include <iostream>
#include "Utilities.h"

Day7::Day7()
{
	std::vector<std::string> lLines{ Utilities::getFileLines("input/Day7.txt") };

	for (std::string const& lLine : lLines)
	{
		mEquations.emplace_back(std::stoull(lLine.substr(0, lLine.find(":"))), std::list<size_t>());
		std::list<size_t>& lValues{ mEquations.back().mValues };

		size_t lPrevPos{ lLine.find(" ") };
		size_t lNextPos{ lLine.find(" ", lPrevPos + 1) };

		while (lPrevPos != std::string::npos)
		{
			lValues.push_back(std::stoull(lLine.substr(lPrevPos + 1, lNextPos - lPrevPos - 1)));

			lPrevPos = lNextPos;
			lNextPos = lLine.find(" ", lPrevPos + 1);
		}
	}
}

size_t Day7::part1()
{
	size_t lRes{ 0 };

	for (auto const& lEquation : mEquations)
	{
		if (checkEquation(lEquation))
		{
			lRes += lEquation.mRes;
		}
	}

	return lRes;
}

size_t Day7::part2()
{
	size_t lRes{ 0 };
	
	for (auto const& lEquation : mEquations)
	{
		if (checkEquation2(lEquation))
		{
			lRes += lEquation.mRes;
		}
	}

	return lRes;
}

bool Day7::checkEquation(Equation const& pEquation) const
{
	if (pEquation.mValues.size() <= 1)
	{
		return pEquation.mRes == pEquation.mValues.front();
	}
	else if (pEquation.mValues.front() > pEquation.mRes)
	{
		return false;
	}

	Equation lAddEquation{ pEquation };
	
	size_t lA{ lAddEquation.mValues.front() };
	lAddEquation.mValues.pop_front();
	size_t lB{ lAddEquation.mValues.front() };
	lAddEquation.mValues.pop_front();

	Equation lMulEquation{ lAddEquation };

	lAddEquation.mValues.push_front(lA + lB);
	lMulEquation.mValues.push_front(lA * lB);

	return checkEquation(lAddEquation) || checkEquation(lMulEquation);
}

bool Day7::checkEquation2(Equation const& pEquation) const
{
	if (pEquation.mValues.size() <= 1)
	{
		return pEquation.mRes == pEquation.mValues.front();
	}
	else if (pEquation.mValues.front() > pEquation.mRes)
	{
		return false;
	}

	Equation lAddEquation{ pEquation };

	size_t lA{ lAddEquation.mValues.front() };
	lAddEquation.mValues.pop_front();
	size_t lB{ lAddEquation.mValues.front() };
	lAddEquation.mValues.pop_front();

	Equation lMulEquation{ lAddEquation };
	Equation lConcatEquation{ lAddEquation };

	lAddEquation.mValues.push_front(lA + lB);
	lMulEquation.mValues.push_front(lA * lB);
	lConcatEquation.mValues.push_front(Utilities::concatNumbers(lA, lB));

	return checkEquation2(lAddEquation) || checkEquation2(lMulEquation) || checkEquation2(lConcatEquation);
}