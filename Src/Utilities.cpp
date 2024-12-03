#include "Utilities.h"

#include <fstream>

std::vector<std::string> Utilities::getFileLines(std::string const& pSrc)
{
    std::vector<std::string> lLines;

    if (std::ifstream lFile{ pSrc }; lFile.is_open()) {
        std::string lLine;
        while (std::getline(lFile, lLine)) {
            lLines.push_back(lLine);
        }
        lFile.close();
    }

    return lLines;
}

std::string Utilities::getFileAsRaw(std::string const& pSrc)
{
    std::ifstream lFile{ pSrc };

    return std::string(std::istreambuf_iterator<char>(lFile), std::istreambuf_iterator<char>());
}
