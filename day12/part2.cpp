/* Day 12, Part 2 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

int
main (int argc, char **argv)
{
    /* Convert from letter grid to number grid because there maay be more
     * that 256 areas.
     */
    std::vector<std::string> letterGrid;
    std::vector<std::vector<int>> numberGrid;
    int id = 0;

    if (argc > 1)
        /* Open file for reading as std::cin: */
        freopen(argv[1], "r", stdin);

    std::string line;
    while (std::getline(std::cin, line))
        letterGrid.push_back(line);

    const int MAX_X = (int) letterGrid[0].size(),
              MAX_Y = (int) letterGrid.size();

    for (auto y = 0; y < MAX_Y; ++y)
    {
        numberGrid.push_back(std::vector<int>(letterGrid[y].size(), -1));
        for (auto x = 0; x < MAX_X; ++x)
        {
            bool leftExtend = x > 0 && letterGrid[y][x] == letterGrid[y][x - 1];
            bool topExtend = y > 0 && letterGrid[y][x] == letterGrid[y - 1][x];
            if (leftExtend && topExtend
                            && numberGrid[y][x - 1] != numberGrid[y - 1][x])
            {
                auto winnerId = std::min(numberGrid[y][x - 1], numberGrid[y - 1][x]),
                     loserId  = std::max(numberGrid[y][x - 1], numberGrid[y - 1][x]);
                numberGrid[y][x] = winnerId;
                for (auto i = 0; i < y + 1; ++i)
                    for (auto j = 0; j < MAX_X; ++j)
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
    
    for (auto y = 0; y < MAX_Y; ++y)
    {
        for (auto x = 0; x < MAX_X; ++x)
            std::cout << std::setw(3) << numberGrid[y][x] << " ";
        std::cout << std::endl;
    }

    struct info { unsigned area, sideCount; };
    std::vector<info> infos(id + 1, {0, 0});
    
    /* Calculate areas first */
    for (auto y = 0; y < MAX_Y; ++y)
        for (auto x = 0; x < MAX_X; ++x)
            ++infos[numberGrid[y][x]].area;

    for (int y = -1; y < MAX_Y; ++y)
    {
        std::vector<int> sides[2];
        for (int x = 0; x < MAX_X; ++x)
        {
            if (y >= 0 && y < MAX_Y - 1)
            {
                if (numberGrid[y][x] != numberGrid[y+1][x])
                {
                    sides[0].push_back(numberGrid[y][x]);
                    sides[1].push_back(numberGrid[y+1][x]);
                }
                else
                {
                    sides[0].push_back(-1);
                    sides[1].push_back(-1);
                }
            }
            else if (y == -1)
                sides[0].push_back(numberGrid[y+1][x]);
            else
                sides[0].push_back(numberGrid[y][x]);
        }
        std::cout << "At y = " << y << ": " << std::endl;
        for (const auto &side : sides)
        {
            if (side.empty())
                continue;
            if (side[0] > -1)
                ++infos[side[0]].sideCount;
            std::cout << side[0] << " ";
            for (size_t i = 1; i < side.size(); ++i)
            {
                std::cout << side[i] << " ";
                if (side[i] > -1 && side[i] != side[i - 1])
                    ++infos[side[i]].sideCount;
            }
            std::cout << std::endl;
        }
    }

    for (int x = -1; x < MAX_X; ++x)
    {
        std::vector<int> sides[2];
        for (int y = 0; y < MAX_Y; ++y)
        {
            if (x >= 0 && x < MAX_X - 1)
            {
                if (numberGrid[y][x] != numberGrid[y][x + 1])
                {
                    sides[0].push_back(numberGrid[y][x]);
                    sides[1].push_back(numberGrid[y][x+1]);
                }
                else
                {
                    sides[0].push_back(-1);
                    sides[1].push_back(-1);
                }
            }
            else if (x == -1)
                sides[0].push_back(numberGrid[y][x+1]);
            else
                sides[0].push_back(numberGrid[y][x]);
        }
        std::cout << "At x = " << x << ": " << std::endl;
        for (const auto &side : sides)
        {
            if (side.empty())
                continue;
            if (side[0] > -1)
                ++infos[side[0]].sideCount;
            std::cout << side[0] << " ";
            for (size_t i = 1; i < side.size(); ++i)
            {
                std::cout << side[i] << " ";
                if (side[i] > -1 && side[i] != side[i - 1])
                    ++infos[side[i]].sideCount;
            }
            std::cout << std::endl;
        }
    }
    
    int totalPrice = 0;
    for (size_t i = 0; i < infos.size(); ++i)
    {
        std::cout << i << ": " << infos[i].area << " " << infos[i].sideCount << std::endl;
        totalPrice += infos[i].area * infos[i].sideCount;
    }

    std::cout << totalPrice << std::endl;

    return 0;
}
