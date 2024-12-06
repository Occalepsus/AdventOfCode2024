#pragma once

#include "DayInterface.h"

#include <map>
#include <set>
#include <list>

#define DAY_CLASS Day5

class Day5 : public DayInterface
{
public:
	Day5();

	~Day5() override = default;

	size_t part1() override;

	size_t part2() override;

private:
	std::map<size_t, std::set<size_t>> mPagesOrdering{};

	std::vector<std::list<size_t>> mPagesLists{};

	static size_t findMiddle(std::list<size_t> const& pList);

	bool isOrdered(std::list<size_t> const& pList) const;

	void reorderList(std::list<size_t>& pList);
};
