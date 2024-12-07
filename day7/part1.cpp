/* Day 7, Part 1
 *
 * Find whether some combination of operations on provided numbers can produce
 * the desired result.
 */
#include <iostream>
#include <regex>
#include <string>
#include <vector>

int
main (void)
{
    uint64_t overallSum = 0;
    std::string line;
    std::regex re(R"((\d+))");

next_line:
    while (std::getline(std::cin, line))
    {
        uint64_t target;
        std::vector<uint64_t> nums;
        auto begin = std::sregex_iterator(line.begin(), line.end(), re);
        auto end = std::sregex_iterator();
        for (std::sregex_iterator i = begin; i != end; ++i)
            if (i == begin)
                target = std::stoull((*i)[1].str());
            else
                nums.push_back(std::stoull((*i)[1].str()));
        /* There are two operations: + and *.   To iterate over all of them,
         * we will use a bitmask where + is 0 and * is 1.  The assumption is
         * that there are at most 65 numbers.
         */
        const unsigned numOps = nums.size() - 1;
        if (numOps > sizeof(uint64_t) * 8)
        {
            std::cerr << "Too many numbers in the input!" << std::endl;
            return 1;
        }
        const uint64_t max = 1ull << numOps;
        for (uint64_t opsMask = 0; opsMask < max; ++opsMask)
        {
            uint64_t sum = nums[0];
            for (unsigned i = 0; i < numOps; ++i)
            {
                if (opsMask & (1ull << i))
                    sum *= nums[i + 1];
                else
                    sum += nums[i + 1];
                if (sum > target)
                    break;
            }
            if (sum == target)
            {
                overallSum += target;
                goto next_line;
            }
        }
    }

    std::cout << overallSum << std::endl;
    return 0;
}
