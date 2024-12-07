#include "Day6.h"

#include <iostream>
#include "Utilities.h"

#include <map>
#include <set>

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
	std::set<int> lObstaclesPos{};

	int lCurIdx{ static_cast<int>(mGrid.find('^')) };
	int lNextIdx{ lCurIdx };

	EDir lCurDir{ EDir::UP };

	while (getNextPosition(mGrid, lNextIdx, lCurDir))
	{
		// If move, copy grid and place obstacle in next visited position (that means dir is not modified)
		if (lNextIdx != lCurIdx && mGrid[lNextIdx == '.'] && lObstaclesPos.find(lNextIdx) == lObstaclesPos.end())
		{
			std::string lGridCopy{ mGrid };
			lGridCopy[lNextIdx] = 'O';

			// If no obstacles were placed at this position and loop is found, add it to the set
			if (travelGridAndCheckLoop(lGridCopy, lCurIdx, lCurDir))
			{
				lObstaclesPos.insert(lNextIdx);

				//std::cout << lGridCopy << "\n\n";
			}
		}

		lCurIdx = lNextIdx;
		mGrid[lCurIdx] = getDirChar(lCurDir);
	}
	
	return lObstaclesPos.size();
}

char Day6::getDirChar(EDir pDir)
{
	switch (pDir)
	{
	case EDir::UP:
		return '^';
	case EDir::RIGHT:
		return '>';
	case EDir::DOWN:
		return 'v';
	case EDir::LEFT:
		return '<';
	default:
		std::cout << "ERROR\n";
		return 'X';
	}
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
	else if (pGrid[lNextIdx] != '#' && pGrid[lNextIdx] != 'O')
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
		pGrid[lCurIdx] = getDirChar(lCurDir);
	}
}

bool Day6::travelGridAndCheckLoop(std::string& pGrid, int pCurIdx, EDir pCurDir) const
{
	std::set<std::pair<int, EDir>> mPositions{};

	int lNextIdx{ pCurIdx };
	while (getNextPosition(pGrid, lNextIdx, pCurDir))
	{
		// If turn, check if it has already been taken
		if (lNextIdx == pCurIdx)
		{
			auto lIt{ mPositions.find(std::pair<int, EDir>(pCurIdx, pCurDir)) };

			// If this position and orientation has already been visited, return true
			if (lIt != mPositions.end())
			{
				return true;
			}
			// Else, store it
			else
			{
				mPositions.emplace(pCurIdx, pCurDir);
			}
		}

		pCurIdx = lNextIdx;
		pGrid[pCurIdx] = getDirChar(pCurDir);
	}
	return false;
}

inline size_t Day6::countVisited() const
{
	size_t lUp{ static_cast<size_t>(std::count(mGrid.begin(), mGrid.end(), '^')) };
	size_t lRight{ static_cast<size_t>(std::count(mGrid.begin(), mGrid.end(), '>')) };
	size_t lDown{ static_cast<size_t>(std::count(mGrid.begin(), mGrid.end(), 'v')) };
	size_t lLeft{ static_cast<size_t>(std::count(mGrid.begin(), mGrid.end(), '<')) };

	return lUp + lRight + lDown + lLeft;
}

/*
	-> 1846 too high
	-> 1740 too high
*/