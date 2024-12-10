/* Day 10, Part 1 */

#include <iostream>
#include <set>
#include <string>
#include <vector>

static void
findScore (const std::vector<std::string> &grid,
        std::set<std::pair<int, int>> &nines, const std::pair<int, int> &pos)
{
    const auto [x, y] = pos;
    const char nextVal = grid[y][x] + 1;
    if (nextVal <= '9')
    {
        if (x > 0 && grid[y][x - 1] == nextVal)
            findScore(grid, nines, std::make_pair(x - 1, y));
        if (y > 0 && grid[y - 1][x] == nextVal)
            findScore(grid, nines, std::make_pair(x, y - 1));
        if (x + 1 < grid[y].size() && grid[y][x + 1] == nextVal)
            findScore(grid, nines, std::make_pair(x + 1, y));
        if (y + 1 < grid.size() && grid[y + 1][x] == nextVal)
            findScore(grid, nines, std::make_pair(x, y + 1));
    }
    else
        nines.insert(pos);
}

int
main (void)
{
    std::string line;
    std::vector<std::pair<int, int>> trailHeads;
    std::vector<std::string> grid;

    int y = 0;
    while (std::getline(std::cin, line))
    {
        size_t x = 0;
        while ((x = line.find("0", x)) != std::string::npos)
        {
            trailHeads.push_back(std::make_pair(x, y));
            ++x;
        }
        grid.push_back(line);
        ++y;
    }

    size_t score = 0;
    std::set<std::pair<int, int>> nines;
    for (const auto &pos : trailHeads)
    {
        nines.clear();
        findScore(grid, nines, pos);
        score += nines.size();
    }

    std::cout << score << std::endl;
    return 0;
}
