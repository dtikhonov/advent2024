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
        const unsigned numOps = nums.size() - 1;
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
                    sum = std::stoull(std::to_string(sum)
                                            + std::to_string(nums[i + 1]));
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
