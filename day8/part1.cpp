/* Day 8, Part 1
 *
 * Collect locations of antennas by letter and then process each bucket.
 */
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

struct pos {
    int x, y;
    int operator<(const pos &p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    }
};

static void
processAntennaSet (const std::vector<pos> &positions,
            const int maxX, const int maxY, std::set<pos> &antinodeLocations)
{
    for (size_t i = 0; i < positions.size(); ++i)
        for (size_t j = i + 1; j < positions.size(); ++j)
        {
            const pos &a = positions[i], &b = positions[j];
            const int dX = b.x - a.x, dY = b.y - a.y;
            const pos possibleAntinodes[] = {
                pos{a.x - dX, a.y - dY},
                pos{b.x + dX, b.y + dY},
            };
            for (const pos &pos : possibleAntinodes)
                if (pos.x >= 0 && pos.x < maxX && pos.y >= 0 && pos.y < maxY)
                    antinodeLocations.insert(pos);
        }
}

int
main (void)
{
    std::string line;
    std::map<char, std::vector<pos>> antennas;
    std::set<pos> antinodeLocations;

    int x, y;   // Outside the loop to indicate dimensions of the grid
    for (y = 0; std::getline(std::cin, line); ++y)
        for (x = 0; x < line.size(); ++x)
            if (isalnum(line[x]))
            {
                auto it = antennas.find(line[x]);
                if (it == antennas.end())
                    antennas[line[x]] = std::vector<pos>({pos{x, y}});
                else
                    it->second.emplace_back(pos{x, y});
            }

    for (const auto &antenna : antennas)
        processAntennaSet(antenna.second, x, y, antinodeLocations);

    std::cout << antinodeLocations.size() << std::endl;
    return 0;
}
