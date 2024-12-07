#pragma once

#include <vector>
#include <string>

namespace Utilities
{
	std::vector<std::string> getFileLines(std::string const& pSrc);

	std::string getFileAsRaw(std::string const& pSrc);

	inline size_t concatNumbers(size_t pA, size_t pB)
	{
		size_t lB_copy{ pB };

		while (lB_copy > 0)
		{
			pA *= 10;
			lB_copy /= 10;
		}

		return pA + pB;
	}
};

