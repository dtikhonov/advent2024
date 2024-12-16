/* Day 14, Part 2 */

#include <iostream>
#include <string>
#include <vector>

enum { LBOX = '[', RBOX = ']', WALL = '#', EMPTY = '.', ROBOT = '@', };

static bool
move (std::vector<std::string> &grid, int x, int y, char dir, bool commit)
{
    if (grid[y][x] == WALL)
        return false;
    if (grid[y][x] == EMPTY)
        return true;
    if (dir == '<' || dir == '>')
    {
        auto newX = x;
        if (dir == '<')
            --newX;
        else
            ++newX;
        /* XXX The dry-run/commit mechanism is not necessary for the horizontal
         * moves.  This can be refactored.
         */
        if (move(grid, newX, y, dir, false))
        {
            if (commit)
            {
                move(grid, newX, y, dir, true);
                grid[y][newX] = grid[y][x];
                grid[y][x] = EMPTY;
            }
            return true;
        }
        else
            return false;
    }
    else
    {
        int otherX, newY;
        if (grid[y][x] == LBOX)
            otherX = x + 1;
        else
            otherX = x - 1;
        if (dir == '^')
            newY = y - 1;
        else
            newY = y + 1;
        if (move(grid, otherX, newY, dir, false)
                                        && move(grid, x, newY, dir, false))
        {
            if (commit)
            {
                move(grid, otherX, newY, dir, true);
                move(grid, x, newY, dir, true);
                grid[newY][x] = grid[y][x];
                grid[newY][otherX] = grid[y][otherX];
                grid[y][x] = EMPTY;
                grid[y][otherX] = EMPTY;
            }
            return true;
        }
        else
            return false;
    }
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
        std::string convertedLine;
        for (auto c : line)
            switch (c)
            {
                case 'O': convertedLine.append("[]"); break;
                case '.': convertedLine.append(".."); break;
                case '#': convertedLine.append("##"); break;
                case '@':
                    robotX = convertedLine.size();
                    robotY = grid.size();
                    convertedLine.append("@.");
                    break;
            }
        grid.push_back(convertedLine);
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
        if (move(grid, newX, newY, dir, false))
        {
            move(grid, newX, newY, dir, true);
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
            if (grid[y][x] == LBOX)
                sum += 100 * y + x;

    std::cout << "Sum: " << sum << '\n';
    return 0;
}