#include "Day4.h"

#include <iostream>
#include "Utilities.h"

Day4::Day4()
{
	mGrid = Utilities::getFileAsRaw("input/Day4.txt");

	mWidth = mGrid.find('\n');
	mHeight = std::count(mGrid.begin(), mGrid.end(), '\n') + 1;

	mFoundImage = std::string(mGrid.size(), '.');

	auto lIt{ mFoundImage.begin() };
	for (;;)
	{
		if (std::distance(lIt, mFoundImage.end()) > mWidth)
		{
			lIt += mWidth;
		}
		else
		{
			break;
		}

		*lIt = '\n';

		lIt++;
	}
}

size_t Day4::part1()
{
	size_t lRes{ 0 };

	for (size_t lEltIdx{ 0 }; lEltIdx < mGrid.size(); lEltIdx++)
	{
		if (mGrid[lEltIdx] == mcXMAS[0])
		{
			for (int lDir{0}; lDir < static_cast<int>(EDir::NbEDir); lDir++)
			{
				if (findXMASAtDir(lEltIdx, static_cast<EDir>(lDir)))
				{
					lRes++;
				}
			}
		}
	}

	std::cout << mFoundImage << "\n\n";

	return lRes;
}

size_t Day4::part2()
{
	size_t lRes{ 0 };

	for (size_t lEltIdx{ 0 }; lEltIdx < mGrid.size(); lEltIdx++)
	{
		if (mGrid[lEltIdx] == 'A')
		{
			lRes += coundX_MAXAt(lEltIdx);
		}
	}

	std::cout << mFoundImage << "\n\n";

	return lRes;
}

bool Day4::findXMASAtDir(size_t pPos, EDir pDir)
{
	bool lFound{ true };

	size_t lPosX{ pPos % (mWidth + 1) };
	size_t lPosY{ pPos / (mWidth + 1) };

	switch (pDir)
	{
	case EDir::N:
		lFound = lPosY + 1 >= mcXMAS.size();
		break;
	case EDir::E:
		lFound = lPosX + mcXMAS.size() <= mWidth;
		break;
	case EDir::S:
		lFound = lPosY + mcXMAS.size() <= mHeight;
		break;
	case EDir::W:
		lFound = lPosX + 1 >= mcXMAS.size();
		break;
	case EDir::NE:
		lFound = lPosY + 1 >= mcXMAS.size() && lPosX + mcXMAS.size() <= mWidth;
		break;
	case EDir::SE:
		lFound = lPosY + mcXMAS.size() <= mHeight && lPosX + mcXMAS.size() <= mWidth;
		break;
	case EDir::SW:
		lFound = lPosY + mcXMAS.size() <= mHeight && lPosX + 1 >= mcXMAS.size();
		break;
	case EDir::NW:
		lFound = lPosY + 1 >= mcXMAS.size() && lPosX + 1 >= mcXMAS.size();
		break;
	default:
		break;
	}

	if (lFound)
	{
		std::vector<size_t> lLettersPos{};
		lLettersPos.push_back(pPos);

		for (size_t lXMASIdx{ 1 }; lXMASIdx < mcXMAS.size(); lXMASIdx++)
		{
			size_t lIdx{ pPos };

			switch (pDir)
			{
			case EDir::N:
				lIdx -= (mWidth + 1) * lXMASIdx;
				break;
			case EDir::E:
				lIdx += lXMASIdx;
				break;
			case EDir::S:
				lIdx += (mWidth + 1) * lXMASIdx;
				break;
			case EDir::W:
				lIdx -= lXMASIdx;
				break;
			case EDir::NE:
				lIdx -= mWidth * lXMASIdx;
				break;
			case EDir::SE:
				lIdx += (mWidth + 2) * lXMASIdx;
				break;
			case EDir::SW:
				lIdx += mWidth * lXMASIdx;
				break;
			case EDir::NW:
				lIdx -= (mWidth + 2) * lXMASIdx;
				break;
			default:
				break;
			}

			if (mGrid[lIdx] != mcXMAS[lXMASIdx])
			{
				lFound = false;
				break;
			}
			else
			{
				lLettersPos.push_back(lIdx);
			}
		}

		if (lFound)
		{
			for (size_t i{ 0 }; i < mcXMAS.size(); i++)
			{
				mFoundImage[lLettersPos[i]] = mcXMAS[i];
			}
		}
	}

	return lFound;
}

std::vector<Day4::EDir> Day4::findMASAround(size_t pPos) const
{
	std::vector<EDir> lDirs{};

	size_t lPosX{ pPos % (mWidth + 1) };
	size_t lPosY{ pPos / (mWidth + 1) };

	if (lPosX > 0 && lPosX + 1 < mWidth && lPosY > 0 && lPosY + 1 < mHeight)
	{
		const std::vector<char> lAroundChars
		{
			mGrid[pPos - (mWidth + 1)],	// N
			mGrid[pPos - mWidth],		// NE
			mGrid[pPos + 1],			// E
			mGrid[pPos + (mWidth + 2)],	// SE
			mGrid[pPos + (mWidth + 1)],	// S
			mGrid[pPos + mWidth],		// SW
			mGrid[pPos - 1],			// W
			mGrid[pPos - (mWidth + 2)],	// NW
		};

		for (size_t lDir{ 0 }; lDir < static_cast<size_t>(EDir::NbEDir); lDir++)
		{
			if (lAroundChars[lDir] == 'S' && lAroundChars[(lDir + 4) % 8] == 'M')
			{
				lDirs.push_back(static_cast<EDir>(lDir));
			}
		}
	}

	return lDirs;
}

int Day4::coundX_MAXAt(size_t pPos)
{
	int lRes{ 0 };

	if (auto lDirs{ findMASAround(pPos) }; lDirs.size() > 1)
	{
		//bool lVert{ std::find(lDirs.begin(), lDirs.end(), EDir::N) != lDirs.end()
		//	|| std::find(lDirs.begin(), lDirs.end(), EDir::S) != lDirs.end() };
		//
		//bool lHor{ std::find(lDirs.begin(), lDirs.end(), EDir::E) != lDirs.end()
		//	|| std::find(lDirs.begin(), lDirs.end(), EDir::W) != lDirs.end() };

		bool lRBot{ std::find(lDirs.begin(), lDirs.end(), EDir::SE) != lDirs.end()
			|| std::find(lDirs.begin(), lDirs.end(), EDir::NW) != lDirs.end() };

		bool lRTop{ std::find(lDirs.begin(), lDirs.end(), EDir::NE) != lDirs.end()
			|| std::find(lDirs.begin(), lDirs.end(), EDir::SW) != lDirs.end() };

		//if (lHor && lVert)
		//{
		//	lRes++;

		//	mFoundImage[pPos] = mGrid[pPos];
		//	mFoundImage[pPos - (mWidth + 1)] = mGrid[pPos - (mWidth + 1)];
		//	mFoundImage[pPos + 1] = mGrid[pPos + 1];
		//	mFoundImage[pPos + (mWidth + 1)] = mGrid[pPos + (mWidth + 1)];
		//	mFoundImage[pPos - 1] = mGrid[pPos - 1];
		//}

		if (lRBot && lRTop)
		{
			lRes++;

			mFoundImage[pPos] = mGrid[pPos];
			mFoundImage[pPos - mWidth] = mGrid[pPos - mWidth];
			mFoundImage[pPos + (mWidth + 2)] = mGrid[pPos + (mWidth + 2)];
			mFoundImage[pPos + mWidth] = mGrid[pPos + mWidth];
			mFoundImage[pPos - (mWidth + 2)] = mGrid[pPos - (mWidth + 2)];
		}
	}

	return lRes;
}
