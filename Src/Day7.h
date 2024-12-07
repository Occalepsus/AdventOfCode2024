#pragma once

#include "DayInterface.h"

#include <list>

#define DAY_CLASS Day7

class Day7 : public DayInterface
{
public:
	Day7();

	~Day7() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	struct Equation
	{
		size_t mRes{ 0 };

		std::list<size_t> mValues{};

		explicit Equation(size_t pRes) : mRes(pRes) {};

		Equation(size_t pRes, std::list<size_t> pValues) : mRes(pRes), mValues(std::move(pValues)) {};
	};

	std::vector<Equation> mEquations{};

	bool checkEquation(Equation const& pEquation) const;

	bool checkEquation2(Equation const& pEquation) const;
};
