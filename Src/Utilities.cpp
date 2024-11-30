#include "Utilities.h"

#include <fstream>

std::vector<std::string> Utilities::getFileLines(std::string const& pSrc)
{
    std::vector<std::string> lLines;
    std::ifstream lFile{ pSrc };

    if (lFile.is_open()) {
        std::string lLine;
        while (std::getline(lFile, lLine)) {
            lLines.push_back(lLine);
        }
        lFile.close();
    }

    return lLines;
}
