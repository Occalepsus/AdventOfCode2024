#pragma once

#include "DayInterface.h"

#define DAY_CLASS Day3

class Day3 : public DayInterface
{
public:
	Day3();

	~Day3() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	std::string mData{};
};

