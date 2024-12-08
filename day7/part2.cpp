/* Day 7, Part 2
 *
 * Find whether some combination of operations on provided numbers can produce
 * the desired result.
 * 
 * We build on previous result.  The tricky part here is how to represent a
 * sequence of operators that can take on 3, not 2, values.  We use a vector.
 */
#include <iostream>
#include <regex>
#include <string>
#include <vector>

enum op { ADD, MUL, CAT, N_OPS};

/* Return false if no inrement is possible as we reached the maximum value */
static bool
increment (std::vector<op> &ops)
{
    for (unsigned i = 0; i < ops.size(); ++i)
    {
        if (ops[i] == N_OPS - 1)
        {
            ops[i] = (op) 0;
            if (i == ops.size() - 1)
                return false;
        }
        else
        {
            ops[i] = (op) (ops[i] + 1);
            return true;
        }
    }
    return false;
}

int
main (void)
{
    static const uint64_t len2num[] = {1, 10, 100, 1000, 10000, 100000, 1000000,
        10000000, 100000000, 1000000000, 10000000000, 100000000000,
        1000000000000, 10000000000000, 100000000000000, 1000000000000000};
    uint64_t overallSum = 0;
    uint64_t target, nums[sizeof(uint64_t) * 8];
    uint64_t multipliers[sizeof(uint64_t) * 8];
    unsigned numCount;
    std::string line;
    std::regex re(R"((\d+))");

next_line:
    while (std::getline(std::cin, line))
    {
        auto begin = std::sregex_iterator(line.begin(), line.end(), re);
        auto end = std::sregex_iterator();
        numCount = 0;
        for (std::sregex_iterator i = begin; i != end; ++i)
            if (i == begin)
                target = std::stoull((*i)[1].str());
            else if (numCount < sizeof(nums) / sizeof(nums[0]))
            {
                nums[numCount] = std::stoull((*i)[1].str());
                multipliers[numCount] = len2num[(*i)[1].length()];
                ++numCount;
            }
            else
            {
                std::cerr << "Too many numbers in line" << std::endl;
                return 1;
            }
        const unsigned numOps = numCount - 1;
        std::vector<op> ops(numOps, (op) /* Use zero in order not to depend
            on any particular enum values */ 0);
        do
        {
            uint64_t sum = nums[0];
            for (unsigned i = 0; i < numOps; ++i)
            {
                switch (ops[i])
                {
                case ADD:
                    sum += nums[i + 1];
                    break;
                case MUL:
                    sum *= nums[i + 1];
                    break;
                case CAT:
                    /* Catenate as strings: 123 CAT 94 => 12394 */
                    sum = sum * multipliers[i + 1] + nums[i + 1];
                    break;
                }
                if (sum > target)
                    break;
            }
            if (sum == target)
            {
                overallSum += target;
                goto next_line;
            }
        }
        while (increment(ops));
    }

    std::cout << overallSum << std::endl;
    return 0;
}
