/* Day 6, Part 2
 *
 * We now want to count the number of intersections where we can introduce
 * a loop.  To do this, first run the path to generate the list of all the
 * positions visited.  Then, introduce an obstacle at each position and
 * check for loop.
 * 
 * As usual, no input validation is performed.
 */
#include <iostream>
#include <string>
#include <vector>
#include <set>

static void
printMap (const std::vector<std::string> &map)
{
    std::cout << "---" << std::endl;
    for (const auto &line : map)
        std::cout << line << std::endl;
    std::cout << std::endl;
}

int
main (void)
{
    std::vector<std::string> masterMap, map;
    std::string str;
    struct pos {
        int operator<(const pos &p) const {
            return x < p.x || (x == p.x && y < p.y);
        }
        int x, y;
    } begin, cur, next;

    enum direction { D_UP, D_RIGHT, D_DOWN, D_LEFT, } masterDir, dir;

    // 'P'.  We need the lower bits to store direction records
    constexpr char P = 0x50;

    enum square_type { ST_OBSTRUCTION = '#',
                       ST_EMPTY = '.',
                       /* Start with 'a' so that we can print them */
                       ST_VISITED_UP = P + (1 << D_UP),
                       ST_VISITED_DOWN = P + (1<< D_DOWN),
                       ST_VISITED_RIGHT = P + (1<< D_RIGHT),
                       ST_VISITED_LEFT = P + (1<< D_LEFT), };

    while (std::getline(std::cin, str))
    {
        const auto off = str.find_first_of("^v<>");
        if (off != std::string::npos)
        {
            begin.x = off;
            begin.y = masterMap.size();
            switch (str[off])
            {
                case '^': masterDir = D_UP; break;
                case 'v': masterDir = D_DOWN; break;
                case '<': masterDir = D_LEFT; break;
                case '>': masterDir = D_RIGHT; break;
            }
            str[off] = P + (1 << masterDir);
        }
        masterMap.push_back(str);
    }

    /* Generate a list of visited positions */
    std::set<pos> visistedPositions;
    map = masterMap;
    cur = begin;
    dir = masterDir;
    while (true)
    {
        next = cur;
        switch (dir)
        {
            case D_UP: --next.y; break;
            case D_DOWN: ++next.y; break;
            case D_LEFT: --next.x; break;
            case D_RIGHT: ++next.x; break;
        }
        if (next.y < 0 || next.y >= map.size() ||
            next.x < 0 || next.x >= map[next.y].size())
            break;
        if (map[next.y][next.x] == ST_OBSTRUCTION)
        {
            dir = static_cast<direction>((dir + 1) % 4);
            continue;
        }
        visistedPositions.insert(next);
        cur = next;
    }

    /* Introduce an obstacle at each of visited positions, one at a time,
     * and check for loops.
     */
    unsigned loopCount = 0;
    for (const auto &pos : visistedPositions)
    {
        if (pos.x == begin.x && pos.y == begin.y)
            continue;   // We cannot put an obstacle at the starting point
        map = masterMap;
        map[begin.y][begin.x] = P + (1 << masterDir);
        map[pos.y][pos.x] = ST_OBSTRUCTION;
        cur = begin;
        dir = masterDir;
        while (true)
        {
            next = cur;
            switch (dir)
            {
                case D_UP: --next.y; break;
                case D_DOWN: ++next.y; break;
                case D_LEFT: --next.x; break;
                case D_RIGHT: ++next.x; break;
            }
            if (next.y < 0 || next.y >= map.size() ||
                next.x < 0 || next.x >= map[next.y].size())
                break;
            if (map[next.y][next.x] == ST_OBSTRUCTION)
            {
                dir = static_cast<direction>((dir + 1) % 4);
                continue;
            }
            if (map[next.y][next.x] == ST_EMPTY)
                map[next.y][next.x] = P + (1 << dir);
            else
            {
                if ((map[next.y][next.x] & 0xF) & (1 << dir))
                {
                    // std::cout << "Loop with obstruction at " << pos.y << ", " << pos.x << std::endl;
                    ++loopCount;
                    break;
                }
                map[next.y][next.x] |= 1 << dir;
            }
            cur = next;
        }
    }

    std::cout << loopCount << std::endl;
    return 0;
}
