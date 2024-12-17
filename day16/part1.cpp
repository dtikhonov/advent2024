/* Day 16, Part 1 */

#include <iostream>
#include <climits>
#include <string>
#include <map>
#include <deque>
#include <vector>

enum dir { EAST, SOUTH, WEST, NORTH, N_DIRS };

struct point {
    int x, y;
    bool operator==(const point &other) const
    {
        return x == other.x && y == other.y;
    }
};

struct position {
    point pt;
    enum dir dir;
    bool operator<(const position &other) const
    {
        return pt.x < other.pt.x
           || (pt.x == other.pt.x && pt.y < other.pt.y)
           || (pt.x == other.pt.x && pt.y == other.pt.y && dir < other.dir)
        ;
    }
};

int
main (void)
{
    using cost_t = int;
    constexpr cost_t MOVE_COST = 1, TURN_COST = 1000;

    std::vector<std::string> grid;
    std::map<position, cost_t> alreadyConsidered;
    point start, end;

    std::string line;
    while (std::getline(std::cin, line))
    {
        if (auto off = line.find('S'); off != std::string::npos)
            start = point{static_cast<int>(off), static_cast<int>(grid.size())};
        if (auto off = line.find('E'); off != std::string::npos)
            end = point{static_cast<int>(off), static_cast<int>(grid.size())};
        grid.push_back(line);
    }

    cost_t minCost = INT_MAX;

    const auto startMove = std::make_pair(position{start, EAST}, 0);
    alreadyConsidered.insert(startMove);
    std::deque<std::pair<position, cost_t>> queue = { startMove };

    do
    {
        const auto [pos, cost] = queue.back(); queue.pop_back();
        if (pos.pt == end)
            /* Because of pruning, each new found solution is the new minimum */
            minCost = cost;
        else
        {
            std::pair<position, cost_t> possibleMoves[] = {
                std::make_pair(pos, cost + MOVE_COST),
                std::make_pair(pos, cost + TURN_COST),
                std::make_pair(pos, cost + TURN_COST),
            };
            switch (pos.dir)
            {
                case EAST:  possibleMoves[0].first.pt.x += 1; break;
                case SOUTH: possibleMoves[0].first.pt.y += 1; break;
                case WEST:  possibleMoves[0].first.pt.x -= 1; break;
                default:    possibleMoves[0].first.pt.y -= 1; break;
            }
            possibleMoves[1].first.dir = static_cast<dir>((pos.dir + 1) % N_DIRS);
            possibleMoves[2].first.dir = static_cast<dir>((pos.dir + N_DIRS - 1) % N_DIRS);
            for (const auto &nextMove : possibleMoves)
            {
                const auto &[newPos, cost] = nextMove;
                if (cost < minCost && grid[newPos.pt.y][newPos.pt.x] != '#')
                {
                    auto it = alreadyConsidered.find(newPos);
                    if (it == alreadyConsidered.end())
                    {
                        queue.emplace_back(nextMove);
                        alreadyConsidered.insert(nextMove);
                    }
                    else if (it->second > cost)
                    {
                        it->second = cost;
                        queue.emplace_back(nextMove);
                    }
                }
            }
        }
    }
    while (!queue.empty());

    std::cout << "Min: " << minCost << std::endl;

    return 0;
}
