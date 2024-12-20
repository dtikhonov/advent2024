/* Day 20, Part 1 */

#include <iostream>
#include <limits>
#include <string>
#include <deque>
#include <map>
#include <vector>

using position = std::pair<size_t, size_t>;

static int
findPath (const std::vector<std::string> &grid,
                    const position &startPos, const position &endPos)
{
    int minCost = std::numeric_limits<int>::max();

    auto startingMove = std::make_pair(startPos, 0);
    std::deque<std::pair<position, int>> queue = { startingMove };
    std::map<position, int> visited = { startingMove };

    do
    {
        const auto [pos, cost] = queue.back(); queue.pop_back();
        if (pos == endPos)
            minCost = cost;
        else
        {
            const auto possibleMoves = {
                std::make_pair(position{pos.first - 1, pos.second}, cost + 1),
                std::make_pair(position{pos.first + 1, pos.second}, cost + 1),
                std::make_pair(position{pos.first, pos.second - 1}, cost + 1),
                std::make_pair(position{pos.first, pos.second + 1}, cost + 1),
            };
            for (const auto &move : possibleMoves)
            {
                const auto &[newPos, newCost] = move;
                if (newPos.first >= 0 && newPos.first < grid[0].size() &&
                    newPos.second >= 0 && newPos.second < grid.size() &&
                    grid[newPos.second][newPos.first] != '#')
                {
                    auto it = visited.find(newPos);
                    if (it == visited.end())
                    {
                        queue.push_back(move);
                        visited.insert(move);
                    }
                    else if (newCost < it->second)
                    {
                        it->second = newCost;
                        queue.push_back(move);
                    }
                }
            }
        }
    }
    while (!queue.empty());

    return minCost;
}

int
main (void)
{
    std::vector<std::string> grid;
    position startPos, endPos;

    std::string line;
    while (std::getline(std::cin, line))
    {
        if (auto off = line.find('S'); off != std::string::npos)
            startPos = { off, grid.size() };
        if (auto off = line.find('E'); off != std::string::npos)
            endPos = { off, grid.size() };
        grid.push_back(line);
    }

    const auto originalCost = findPath(grid, startPos, endPos);
    std::cout << "original cost: " << originalCost << std::endl;
    
    unsigned hundredSavedCount = 0;
    for (size_t y = 1; y < grid.size() - 1; ++y)
    {
        std::cout << "Processing row " << y << std::endl;
        for (size_t x = 1; x < grid[y].size() - 1; ++x)
            if (grid[y][x] == '#')
            {
                grid[y][x] = '.';
                const auto cost = findPath(grid, startPos, endPos);
                if (cost + 100 <= originalCost)
                    ++hundredSavedCount;
                grid[y][x] = '#';
            }
    }

    std::cout << "hundred saved count: " << hundredSavedCount << std::endl;
    return 0;
}