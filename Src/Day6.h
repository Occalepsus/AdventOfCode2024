#pragma once

#include "DayInterface.h"

#define DAY_CLASS Day6

class Day6 : public DayInterface
{
public:
	enum class EDir
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
		NB_DIR
	};

	Day6();

	~Day6() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	std::string mGrid{};

	size_t mWidth{ 0 };
	size_t mHeight{ 0 };

	std::string mFoundImage{};

	static char getDirChar(EDir pDir);

	bool getNextPosition(std::string const& pGrid, int& pCurIdx, EDir& pCurDir) const;

	void travelGrid(std::string& pGrid) const;

	bool travelGridAndCheckLoop(std::string& pGrid, int pCurIdx, EDir pCurDir) const;

	inline size_t countVisited() const;
};
