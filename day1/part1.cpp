#include <algorithm>
#include <iostream>
#include <vector>

int
main (void)
{
    int64_t sum = 0, num;
    std::vector<int64_t> numbers[2];
    int idx = 0;
    
    while (std::cin >> num)
    {
        numbers[idx].push_back(num);
        idx = (idx + 1) % 2;
    }
    
    /* Sort numbers[0] and numbers[1] */
    std::sort(numbers[0].begin(), numbers[0].end());
    std::sort(numbers[1].begin(), numbers[1].end());
    
    for (auto i = 0; i < numbers[0].size(); ++i)
        sum += std::abs(numbers[0][i] - numbers[1][i]);
    
    std::cout << sum << std::endl;
    return 0;
}