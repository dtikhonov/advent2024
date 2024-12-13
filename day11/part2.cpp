/* Day 11, Part 2 */

#include <iostream>
#include <string>
#include <map>
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

struct el { uint64_t num, count; };

static void
addElem (std::map<uint64_t, struct el> &nums, const struct el &el)
{
    if (auto it = nums.find(el.num); it != nums.end())
        it->second.count += el.count;
    else
        nums[el.num] = el;
}

static uint64_t
addCounts (const std::map<uint64_t, struct el> &nums)
{
    uint64_t count = 0;
    for (const auto &[num, el] : nums)
        count += el.count;
    return count;
}

int
main (int argc, char **argv)
{
    const int numIterations = argc > 1 ? std::stoi(argv[1]) : 75;
    std::map<uint64_t, struct el> nums;

    while (std::cin)
    {
        struct el el;
        std::cin >> el.num;
        el.count = 1;       // XXX Assume input has all different numbers
        nums[el.num] = el;
    }

    for (auto i = 0; i < numIterations; ++i)
    {
        decltype(nums) newNums;
        for (const auto &[num, el] : nums)
            if (num == 0)
                addElem(newNums, {1, el.count});
            else if (auto digitCount = countDigits(el.num); digitCount % 2 == 0)
            {
                auto half = digitCount / 2;
                uint64_t divisor = std::pow(10, half);
                addElem(newNums, {el.num / divisor, el.count});
                addElem(newNums, {el.num % divisor, el.count});
            }
            else
                addElem(newNums, {el.num * 2024, el.count});
        nums = newNums;
    }

    std::cout << addCounts(nums) << std::endl;
    return 0;
}