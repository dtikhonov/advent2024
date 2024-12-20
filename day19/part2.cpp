/* Day 19, Part 2 */

#include <iostream>
#include <string>
#include <vector>

int
main (void)
{
    std::vector<std::string> towels;
    std::string line;
    std::getline(std::cin, line);
    /* Split line by /,\s+/ and insert into towels */
    size_t start = 0, end;
    while ((end = line.find(", ", start)) != std::string::npos)
    {
        towels.push_back(line.substr(start, end - start));
        start = end + 2;
    }
    towels.push_back(line.substr(start));

    // Skip empty line
    std::getline(std::cin, line);

    uint64_t totalCount = 0;
    while (std::getline(std::cin, line))
    {
        std::vector<uint64_t> partialCounts(towels.size() + 1, 0);
        partialCounts[0] = 1;
        size_t off;
        for (off = 0; off < line.size(); ++off)
            for (const auto &towel : towels)
                if (line.compare(off, towel.size(), towel) == 0)
                    partialCounts[off + towel.size()] += partialCounts[off];
        totalCount += partialCounts[off];
    }

    std::cout << totalCount << std::endl;
}
