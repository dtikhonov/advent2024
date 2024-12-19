/* Day 18, Part 1 */

#include <iostream>
#include <climits>
#include <string>
#include <map>
#include <deque>
#include <vector>

struct point {
    int x, y;
    bool operator==(const point &other) const
    {
        return x == other.x && y == other.y;
    }
    bool operator<(const point &other) const
    {
        return x < other.x || (x == other.x && y < other.y);
    }
};

int
main (int argc, char **argv)    // Usage prog gridSize fallenByteCount
{
    const int gridSize = std::stoi(argv[1]),
              fallenByteCount = std::stoi(argv[2]);
    std::vector<std::string> grid{ gridSize, std::string(gridSize, '.') };
    std::map<point, int> alreadyConsidered;

    std::string line;
    for (int i = 0; i < fallenByteCount && std::getline(std::cin, line); ++i)
    {
        const auto comma = line.find(',');
        const int x = std::stoi(line.substr(0, comma)),
                  y = std::stoi(line.substr(comma + 1));
        grid[y][x] = '#';
    }

    for (const auto &row : grid) std::cout << row << std::endl;

    int minStepCount = INT_MAX;

    const struct point startPoint{ 0, 0, },
                       endPoint{ gridSize - 1, gridSize - 1 };
    const auto startMove = std::make_pair(startPoint, 0);
    alreadyConsidered.insert(startMove);
    std::deque<std::pair<point, int>> queue = { startMove };

    do
    {
        const auto [pt, stepCount] = queue.back(); queue.pop_back();
        if (pt == endPoint)
            /* Because of pruning, each new found solution is the new minimum */
            minStepCount = stepCount;
        else
        {
            std::pair<struct point, int> possibleMoves[] = {
                std::make_pair(point{pt.x + 1, pt.y}, stepCount + 1),
                std::make_pair(point{pt.x - 1, pt.y}, stepCount + 1),
                std::make_pair(point{pt.x, pt.y + 1}, stepCount + 1),
                std::make_pair(point{pt.x, pt.y - 1}, stepCount + 1),
            };
            for (const auto &nextMove : possibleMoves)
            {
                const auto &[newPt, stepCount] = nextMove;
                if (stepCount < minStepCount && newPt.x >= 0 && newPt.y >= 0
                        && newPt.x < gridSize && newPt.y < gridSize
                        && grid[newPt.y][newPt.x] != '#')
                {
                    auto it = alreadyConsidered.find(newPt);
                    if (it == alreadyConsidered.end())
                    {
                        queue.emplace_back(nextMove);
                        alreadyConsidered.insert(nextMove);
                    }
                    else if (it->second > stepCount)
                    {
                        it->second = stepCount;
                        queue.emplace_back(nextMove);
                    }
                }
            }
        }
    }
    while (!queue.empty());

    std::cout << "Min: " << minStepCount << std::endl;

    return minStepCount < INT_MAX ? 0 : 1;
}
