#pragma once

#include "DayInterface.h"

#define DAY_CLASS Day4

class Day4 : public DayInterface
{
public:
	enum class EDir {
		N = 0,
		NE,
		E,
		SE,
		S,
		SW,
		W,
		NW,
		NbEDir
	};

	Day4();

	~Day4() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	const std::string mcXMAS{ "XMAS" };

	std::string mGrid{};

	size_t mWidth{ 0 };
	size_t mHeight{ 0 };

	std::string mFoundImage{};

	bool findXMASAtDir(size_t pPos, EDir pDir);

	std::vector<EDir> findMASAround(size_t pPos) const;

	int coundX_MAXAt(size_t pPos);
};
