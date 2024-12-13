/* Day 12, Part 1 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

int
main (void)
{
    /* Convert from letter grid to number grid because there maay be more
     * that 256 areas.
     */
    std::vector<std::string> letterGrid;
    std::vector<std::vector<int>> numberGrid;
    int id = 0;

    std::string line;
    while (std::getline(std::cin, line))
        letterGrid.push_back(line);

    for (size_t y = 0; y < letterGrid.size(); ++y)
    {
        numberGrid.push_back(std::vector<int>(letterGrid[y].size(), -1));
        for (size_t x = 0; x < letterGrid[y].size(); ++x)
        {
            bool leftExtend = x > 0 && letterGrid[y][x] == letterGrid[y][x - 1];
            bool topExtend = y > 0 && letterGrid[y][x] == letterGrid[y - 1][x];
            if (leftExtend && topExtend
                            && numberGrid[y][x - 1] != numberGrid[y - 1][x])
            {
                auto winnerId = std::min(numberGrid[y][x - 1], numberGrid[y - 1][x]),
                     loserId  = std::max(numberGrid[y][x - 1], numberGrid[y - 1][x]);
                numberGrid[y][x] = winnerId;
                for (size_t i = 0; i < numberGrid.size(); ++i)
                    for (size_t j = 0; j < numberGrid[i].size(); ++j)
                        if (numberGrid[i][j] == loserId)
                            numberGrid[i][j] = winnerId;
            }
            else if (leftExtend)
                numberGrid[y][x] = numberGrid[y][x - 1];
            else if (topExtend)
                numberGrid[y][x] = numberGrid[y - 1][x];
            else
                numberGrid[y][x] = id++;
        }
    }
    
    for (size_t y = 0; y < numberGrid.size(); ++y)
    {
        for (size_t x = 0; x < numberGrid[y].size(); ++x)
            std::cout << std::setw(3) << numberGrid[y][x] << " ";
        std::cout << std::endl;
    }

    struct info { unsigned area, perimeter; };
    std::vector<info> infos(id + 1, {0, 0});

    for (size_t y = 0; y < numberGrid.size(); ++y)
        for (size_t x = 0; x < numberGrid[y].size(); ++x)
        {
            ++infos[numberGrid[y][x]].area;
            infos[numberGrid[y][x]].perimeter +=
                (x == 0 || numberGrid[y][x] != numberGrid[y][x - 1]) +
                (y == 0 || numberGrid[y][x] != numberGrid[y - 1][x]) +
                (x == numberGrid[y].size() - 1 || numberGrid[y][x] != numberGrid[y][x + 1]) +
                (y == numberGrid.size() - 1 || numberGrid[y][x] != numberGrid[y + 1][x]);
        }

    int totalPrice = 0;
    for (size_t i = 0; i < infos.size(); ++i)
        totalPrice += infos[i].area * infos[i].perimeter;

    std::cout << totalPrice << std::endl;

    return 0;
}
