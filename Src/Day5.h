#pragma once

#include "DayInterface.h"

#define DAY_CLASS Day5

class Day5 : public DayInterface
{
public:
	Day5();

	~Day5() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	std::vector<std::string> mData{};
};
