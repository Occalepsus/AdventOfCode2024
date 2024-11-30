#pragma once

#include "DayInterface.h"

#define DAY_CLASS Day1

class Day1 : public DayInterface
{
public:
	Day1();

	~Day1() = default;

	size_t part1() override;

	size_t part2() override;

private:
	std::vector<std::string> mData{};
};

