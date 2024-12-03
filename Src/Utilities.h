#pragma once

#include <vector>
#include <string>

namespace Utilities
{
	std::vector<std::string> getFileLines(std::string const& pSrc);

	std::string getFileAsRaw(std::string const& pSrc);
};

