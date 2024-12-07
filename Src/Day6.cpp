#include "Day6.h"

#include <iostream>
#include "Utilities.h"

Day6::Day6()
{
	mGrid = Utilities::getFileAsRaw("input/Day6.txt");

	mWidth = mGrid.find('\n');
	mHeight = std::count(mGrid.begin(), mGrid.end(), '\n') + 1;
}

size_t Day6::part1()
{
	travelGrid(mGrid);

	std::cout << mGrid << "\n";

	return countVisited();
}

size_t Day6::part2()
{
	size_t lRes{ 0 };

	return lRes;
}

bool Day6::getNextPosition(std::string const& pGrid, int& pCurIdx, EDir& pCurDir) const
{
	int lNextIdx{ pCurIdx };

	switch (pCurDir)
	{
	case EDir::UP:
		lNextIdx -= (mWidth + 1);
		break;
	case EDir::RIGHT:
		lNextIdx++;
		break;
	case EDir::DOWN:
		lNextIdx += (mWidth + 1);
		break;
	case EDir::LEFT:
		lNextIdx--;
		break;
	default:
		std::cout << "ERROR\n";
		break;
	}

	if (lNextIdx < 0 || lNextIdx >= pGrid.size() || pGrid[lNextIdx] == '\n')
	{
		return false;
	}
	else if (pGrid[lNextIdx] != '#')
	{
		pCurIdx = lNextIdx;
	}
	else
	{
		// Turn right
		pCurDir = static_cast<EDir>((static_cast<int>(pCurDir) + 1) % static_cast<int>(EDir::NB_DIR));
	}

	return true;
}

void Day6::travelGrid(std::string& pGrid) const
{
	int lCurIdx{ static_cast<int>(pGrid.find('^')) };

	EDir lCurDir{ EDir::UP };

	while (getNextPosition(pGrid, lCurIdx, lCurDir))
	{
		switch (lCurDir)
		{
		case EDir::UP:
			pGrid[lCurIdx] = '^';
			break;
		case EDir::RIGHT:
			pGrid[lCurIdx] = '>';
			break;
		case EDir::DOWN:
			pGrid[lCurIdx] = 'v';
			break;
		case EDir::LEFT:
			pGrid[lCurIdx] = '<';
			break;
		default:
			std::cout << "ERROR\n";
			break;
		}
	}
}

inline size_t Day6::countVisited() const
{
	size_t lUp{ static_cast<size_t>(std::count(mGrid.begin(), mGrid.end(), '^')) };
	size_t lRight{ static_cast<size_t>(std::count(mGrid.begin(), mGrid.end(), '>')) };
	size_t lDown{ static_cast<size_t>(std::count(mGrid.begin(), mGrid.end(), 'v')) };
	size_t lLeft{ static_cast<size_t>(std::count(mGrid.begin(), mGrid.end(), '<')) };

	return lUp + lRight + lDown + lLeft;
}
