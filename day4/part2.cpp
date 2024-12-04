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
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            xmasCount += lines[i][j] == 'A'
                && 
                i > 0 && j > 0 && i + 1 < rows && j + 1 < cols
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
