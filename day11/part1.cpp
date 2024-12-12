/* Day 11, Part 1 */

#include <iostream>
#include <iterator>
#include <string>
#include <list>
#include <cmath>

static unsigned
countDigits (uint64_t num)
{
    unsigned digitCount = 0;

    do
    {
        num /= 10;
        ++digitCount;
    }
    while (num);

    return digitCount;
}

int
main (void)
{
    std::list<uint64_t> nums;

    std::copy(std::istream_iterator<uint64_t>(std::cin),
              std::istream_iterator<uint64_t>(),
              std::back_inserter(nums));

    for (auto i = 0; i < 25; ++i)
        for (auto num = nums.begin(); num != nums.end(); ++num)
            if (*num == 0)
                *num = 1;
            else if (auto digitCount = countDigits(*num); digitCount % 2 == 0)
            {
                auto half = digitCount / 2;
                uint64_t divisor = std::pow(10, half);
                auto firstHalf = *num / divisor;
                nums.insert(num, firstHalf);
                *num = *num % divisor;
            }
            else
                *num *= 2024;

    std::cout << nums.size() << std::endl;
    return 0;
}
