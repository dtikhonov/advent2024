/* Day 10, Part 2
 * 
 * Taking a different approach from Part 1: let's do a depth-first search
 * using a queue instead of recursion.
 */ 

#include <iostream>
#include <string>
#include <vector>
#include <list>

int
main (void)
{
    std::string line;
    std::list<std::pair<int, int>> positions;
    std::vector<std::string> grid;

    int y = 0;
    while (std::getline(std::cin, line))
    {
        size_t x = 0;
        while ((x = line.find("0", x)) != std::string::npos)
        {
            positions.push_back(std::make_pair(x, y));
            ++x;
        }
        grid.push_back(line);
        ++y;
    }

    unsigned score = 0;
    while (!positions.empty())
    {
        const auto [x, y] = positions.back();
        positions.pop_back();
        const auto val = grid[y][x];
        if (val == '9')
            ++score;
        else
        {
            if (x > 0 && grid[y][x - 1] == val + 1)
                positions.push_back(std::make_pair(x - 1, y));
            if (y > 0 && grid[y - 1][x] == val + 1)
                positions.push_back(std::make_pair(x, y - 1));
            if (x + 1 < grid[y].size() && grid[y][x + 1] == val + 1)
                positions.push_back(std::make_pair(x + 1, y));
            if (y + 1 < grid.size() && grid[y + 1][x] == val + 1)
                positions.push_back(std::make_pair(x, y + 1));
        }
    }

    std::cout << score << std::endl;
    return 0;
}
