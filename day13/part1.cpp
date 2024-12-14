/* Day 13, Part 1 */

#include <iostream>
#include <iterator>
#include <string>
#include <set>
#include <deque>
#include <list>

struct pos {
    unsigned x, y;
    pos operator+(const pos &other) const
    {
        return {x + other.x, y + other.y};
    }
};

struct machine {
    pos buttonA, buttonB, prize;
};

int
main (void)
{
    std::list<machine> machines;
    machine m;
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line.find("Button A") != std::string::npos)
            std::sscanf(line.c_str(), "Button A: X+%u, Y+%u", &m.buttonA.x, &m.buttonA.y);
        else if (line.find("Button B") != std::string::npos)
            std::sscanf(line.c_str(), "Button B: X+%u, Y+%u", &m.buttonB.x, &m.buttonB.y);
        else if (line.find("Prize") != std::string::npos)
        {
            std::sscanf(line.c_str(), "Prize: X=%u, Y=%u", &m.prize.x, &m.prize.y);
            machines.push_back(m);
        }
    }

    constexpr int COST_A = 3, COST_B = 1;
    struct partial {
        struct pos pos;
        std::pair<int, int> moves;
        int tokens;
    };

    int sum = 0;
    for (const auto &machine : machines)
    {
        std::deque<partial> queue;
        int minTokens = -1;
        std::set<std::pair<int, int>> visited;
        queue.emplace_back(partial{pos{0, 0}, {0, 0}, 0});

        do
        {
            auto part= queue.back(); queue.pop_back();
            if (part.pos.x == machine.prize.x && part.pos.y == machine.prize.y)
            {
                if (minTokens == -1 || part.tokens < minTokens)
                    minTokens = part.tokens;
                continue;
            }

            if (part.pos.x + machine.buttonA.x <= machine.prize.x
                        && part.pos.y + machine.buttonA.y <= machine.prize.y)
            {
                auto newMoves = part.moves;
                ++newMoves.first;
                if (visited.find(newMoves) == visited.end())
                {
                    auto newPos = part.pos + machine.buttonA;
                    auto newTokens = part.tokens + COST_A;
                    visited.insert(newMoves);
                    queue.emplace_back(partial{newPos, newMoves, newTokens});
                }
            }

            if (part.pos.x + machine.buttonA.x <= machine.prize.x
                        && part.pos.y + machine.buttonB.y <= machine.prize.y)
            {
                auto newMoves = part.moves;
                ++newMoves.second;
                if (visited.find(newMoves) == visited.end())
                {
                    auto newPos = part.pos + machine.buttonB;
                    auto newTokens = part.tokens + COST_B;
                    visited.insert(newMoves);
                    queue.emplace_back(partial{newPos, newMoves, newTokens});
                }
            }

        }
        while (!queue.empty());
        std::cout << minTokens << std::endl;
        if (minTokens > -1)
            sum += minTokens;
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
