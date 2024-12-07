/* Day 6, part 1
 *
 * As usual, no input validation is performed.
 */
#include <iostream>
#include <string>
#include <vector>

int
main (void)
{
    std::vector<std::string> map;
    std::string str;
    struct pos { int x, y; } cur;
    unsigned distinctVisited = 0;
    
    enum square_type { ST_OBSTRUCTION = '#',
                       ST_EMPTY = '.',
                       ST_VISITED = 'X', };

    enum direction { D_UP, D_RIGHT, D_DOWN, D_LEFT, } dir;

    while (std::getline(std::cin, str))
    {
        const auto off = str.find_first_of("^v<>");
        if (off != std::string::npos)
        {
            cur.x = off;
            cur.y = map.size();
            switch (str[off])
            {
                case '^': dir = D_UP; break;
                case 'v': dir = D_DOWN; break;
                case '<': dir = D_LEFT; break;
                case '>': dir = D_RIGHT; break;
            }
            str[off] = ST_EMPTY;
        }
        map.push_back(str);
    }
    
    while (true)
    {
        pos next = cur;
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
        distinctVisited += map[next.y][next.x] != ST_VISITED;
        cur = next;
        map[cur.y][cur.x] = ST_VISITED;
    }

    std::cout << distinctVisited << std::endl;
    return 0;
}
