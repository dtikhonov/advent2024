#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

int
main (void)
{
    int64_t a, b, score;
    std::vector<int64_t> numbers;
    std::unordered_map<int64_t, int64_t> counts;
    
    while (std::cin >> a >> b)
    {
        numbers.push_back(a);
        auto it = counts.find(b);
        if (it != counts.end())
            ++it->second;
        else
            counts.insert({b, 1});
    }
    
    score = 0;
    for (auto n : numbers)
        if (auto it = counts.find(n); it != counts.end())
            score += it->second * n;
    
    std::cout << score << std::endl;
    return 0;
}