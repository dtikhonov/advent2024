#include <iostream>
#include <vector>

int
main (void)
{
    std::vector<std::string> lines;
    std::string str;
    int rows, cols;
    unsigned xmasCount = 0;

    while (std::getline(std::cin, str))
        lines.push_back(str);

    rows = (int) lines.size(), cols = (int) lines[0].size();
    for (int i = 1; i < rows - 1; ++i)
        for (int j = 1; j < cols - 1; ++j)
            xmasCount += lines[i][j] == 'A'
                /* Check NW and SE: */
                && (
                    (lines[i-1][j-1] == 'S' && lines[i+1][j+1] == 'M')
                    ||
                    (lines[i-1][j-1] == 'M' && lines[i+1][j+1] == 'S')
                   )
                /* Check SW and NE: */
                && (
                    (lines[i+1][j-1] == 'S' && lines[i-1][j+1] == 'M')
                    ||
                    (lines[i+1][j-1] == 'M' && lines[i-1][j+1] == 'S')
                   )
                ;

    std::cout << xmasCount << std::endl;
    return 0;
}
