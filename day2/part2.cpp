#include <iostream>
#include <vector>
#include <sstream>

int
main (void)
{
    std::vector<int> nums;
    size_t skip, curOff;
    unsigned safeCount = 0;
    std::string line;
    
    auto getNextNum = [&nums, &skip, &curOff] (int *num) -> bool
    {
        if (curOff == skip)
            ++curOff;
        if (curOff < nums.size())
        {
            *num = nums[curOff++];
            return true;
        }
        else
            return false;
    };

get_next_line:
    while (std::getline(std::cin, line))
    {
        int temp;
        std::istringstream iss(line);
        nums.clear();
        while (iss >> temp)
            nums.push_back(temp);
        skip = -1;
        do
        {
            int n[2], i = 0, dir;
            curOff = 0;
            (void) getNextNum(&n[0]);
            (void) getNextNum(&n[1]);
            /* Determine direction */
            if (n[0] > n[1])
            {
                if (n[0] - n[1] > 3)
                    goto skip_next;
                dir = 0;
            }
            else if (n[0] < n[1])
            {
                if (n[1] - n[0] > 3)
                    goto skip_next;
                dir = 1;
            }
            else
                goto skip_next;
            /* Read in the rest of the line */
            while (getNextNum(&n[1 & i++]))
            {
                const int &cur = n[1 & (i - 1)], &prev = n[1 & i];
                if (dir == 0)
                {
                    if (!(cur < prev && cur + 3 >= prev))
                        goto skip_next;
                }
                else
                {
                    if (!(cur > prev && prev + 3 >= cur))
                        goto skip_next;
                }
            }
            ++safeCount;
            goto get_next_line;
    skip_next:
            ++skip; 
        }
        while (skip < nums.size());
    }
    
    std::cout << safeCount << std::endl;
    return 0;
}