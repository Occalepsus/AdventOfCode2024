#pragma once

#include <vector>
#include <string>

class DayInterface
{
public:
	DayInterface() = default;

	virtual ~DayInterface() = default;

	virtual size_t part1() = 0;

	virtual size_t part2() = 0;
};