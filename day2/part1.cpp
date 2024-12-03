#include <iostream>
#include <vector>
#include <sstream>

int
main (void)
{
    unsigned safeCount = 0;
    
    std::string line;
get_next_line:
    while (std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        int nums[2], i = 0, dir;
        /* Determine direction */
        iss >> nums[0] >> nums[1];
        if (nums[0] > nums[1])
        {
            if (nums[0] - nums[1] > 3)
                continue;
            dir = 0;
        }
        else if (nums[0] < nums[1])
        {
            if (nums[1] - nums[0] > 3)
                continue;
            dir = 1;
        }
        else
            continue;
        /* Read in the rest of the line */
        while (iss >> nums[1 & i++])
        {
            const int &cur = nums[1 & (i - 1)], &prev = nums[1 & i];
            if (dir == 0)
            {
                if (!(cur < prev && cur + 3 >= prev))
                    goto get_next_line;
            }
            else
            {
                if (!(cur > prev && prev + 3 >= cur))
                    goto get_next_line;
            }
        }
        ++safeCount;
    }
    
    std::cout << safeCount << std::endl;
    return 0;
}