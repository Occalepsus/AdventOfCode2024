#pragma once

#include "DayInterface.h"

#define DAY_CLASS Day1

class Day1 : public DayInterface
{
public:
	Day1();

	~Day1() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	std::vector<int> mLList{};

	std::vector<int> mRList{};
};

