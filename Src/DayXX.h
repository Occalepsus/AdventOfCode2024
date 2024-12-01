#pragma once

#include "DayInterface.h"

#define DAY_CLASS DayXX

class DayXX : public DayInterface
{
public:
	DayXX();

	~DayXX() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	std::vector<std::string> mData{};
};

