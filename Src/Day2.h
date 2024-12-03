#pragma once

#include "DayInterface.h"

#include <list>

#define DAY_CLASS Day2

class Day2 : public DayInterface
{
public:
	Day2();

	~Day2() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	std::vector<std::list<int>> mData{};

	std::list<int>::const_iterator checkErr(std::list<int> const& lList) const;
};

