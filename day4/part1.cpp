#include <iostream>
#include <string>
#include <vector>

static unsigned
countXmas (const std::string &str)
{
    unsigned count = 0;
    size_t pos;

    for (auto needle : {"XMAS", "SAMX"})
    {
        pos = 0;
        while ((pos = str.find(needle, pos)) != std::string::npos)
        {
            ++count;
            pos += 4;
        }
    }

    return count;
}

int
main (void)
{
    std::vector<std::string> lines;
    std::string str;
    int rows, cols;
    unsigned xmasCount = 0;

    while (std::getline(std::cin, str))
    {
        xmasCount += countXmas(str);
        lines.push_back(str);
    }

    rows = (int) lines.size(), cols = (int) lines[0].size();
    for (auto i = 0; i < cols; ++i)
    {
        str.clear();
        for (auto j = 0; j < rows; ++j)
            str.push_back(lines[j][i]);
        xmasCount += countXmas(str);
    }
    
    for (int row = -cols; row < rows + cols; ++row)
    {
        str.clear();
        for (int i = row, col = 0; i >= 0 || col < cols; --i, ++col)
	{
            if (i >= 0 && i < rows && col < cols)
                str.push_back(lines[i][col]);
	}
        xmasCount += countXmas(str);
        str.clear();
        for (int i = row, col = 0; i < rows || col < cols; ++i, ++col)
	{
            if (i >= 0 && i < rows && col < cols)
                str.push_back(lines[i][col]);
	}
        xmasCount += countXmas(str);
    }

    std::cout << xmasCount << std::endl;
    return 0;
}
