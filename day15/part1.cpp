/* Day 14, Part 1 */

#include <iostream>
#include <string>
#include <vector>

enum { BOX = 'O', WALL = '#', EMPTY = '.', ROBOT = '@', };

static bool
move (std::vector<std::string> &grid, int x, int y, char dir)
{
    if (grid[y][x] == WALL)
        return false;
    if (grid[y][x] == EMPTY)
        return true;
    auto newX = x, newY = y;
    switch (dir)
    {
        case '<': --newX; break;
        case '>': ++newX; break;
        case '^': --newY; break;
        case 'v': ++newY; break;
    }
    if (move(grid, newX, newY, dir))
    {
        grid[newY][newX] = grid[y][x];
        grid[y][x] = EMPTY;
        return true;
    }
    else
        return false;
}

static void
display (const std::vector<std::string> &grid)
{
    for (const auto &line : grid)
        std::cout << line << '\n';
}

int
main (int argc, char **argv)
{
    std::vector<std::string> grid;
    std::string line;
    int robotX, robotY, niter;

    niter = argc > 1 ? std::stoi(argv[1]) : -1;

    // Read in the grid
    while (std::getline(std::cin, line))
    {
        if (line.empty())
            break;
        grid.push_back(line);
        if (auto x = line.find(ROBOT); x != std::string::npos)
        {
            robotX = x;
            robotY = grid.size() - 1;
        }
    }

    std::cout << "Initial state:\n";
    display(grid);

    // Now read char by char and follow directions
    int count = 0;
    while (std::cin)
    {
        char dir;
        std::cin >> dir;
        auto newX = robotX, newY = robotY;
        switch (dir)
        {
            case '<': --newX; break;
            case '>': ++newX; break;
            case '^': --newY; break;
            case 'v': ++newY; break;
        }
        if (move(grid, newX, newY, dir))
        {
            grid[robotY][robotX] = EMPTY;
            robotX = newX;
            robotY = newY;
            grid[robotY][robotX] = ROBOT;
        }
        std::cout << "Move " << (char)dir << ":\n";
        display(grid);
        if (niter >= 0 && ++count >= niter)
            break;
    }

    size_t sum = 0;
    for (size_t y = 0; y < grid.size(); ++y)
        for (size_t x = 0; x < grid[y].size(); ++x)
            if (grid[y][x] == BOX)
                sum += 100 * y + x;

    std::cout << "Sum: " << sum << '\n';
    return 0;
}