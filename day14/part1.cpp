/* Day 14, Part 1 */

#include <iostream>
#include <iterator>
#include <string>
#include <set>
#include <deque>
#include <list>

struct pos { int x, y; };

struct robot { pos p, v; };

int
main (int argc, char **argv)    // Usage prog width height niterations
{
    std::list<robot> robots;
    const int width = std::stoi(argv[1]), height = std::stoi(argv[2]),
        niterations = std::stoi(argv[3]);

    std::string line;
    while (std::getline(std::cin, line))
    {
        robot robot;
        std::sscanf(line.c_str(), "p=%d,%d v=%d,%d", &robot.p.x,
                                &robot.p.y, &robot.v.x, &robot.v.y);
        robots.push_back(robot);
    }

    int quadrants[2][2] = {0};

    const int midX = width / 2, midY = height / 2;
    for (auto robot : robots)
    {
        robot.p.x = (robot.p.x + robot.v.x * niterations) % width;
        robot.p.y = (robot.p.y + robot.v.y * niterations) % height;
        if (robot.p.x < 0)
            robot.p.x += width;
        if (robot.p.y < 0)
            robot.p.y += height;
        if (robot.p.x == midX || robot.p.y == midY)
            continue;
        auto leftOfMidX = robot.p.x < midX,
              aboveMidY = robot.p.y < midY;
        ++quadrants[aboveMidY][leftOfMidX];
    }

    const int prod = quadrants[0][0] * quadrants[1][1] *
                                        quadrants[0][1] * quadrants[1][0];
    std::cout << prod << std::endl;

    return 0;
}