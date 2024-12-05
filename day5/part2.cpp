/* Day 5, part 2.  The idea is to convert the rules into regular expressions
 * and find violations that way.  Building on Part 1, we now use the offsets
 * of the matches to swap the numbers.  A large optimization is to only check
 * the rules that the middle number might violate.
 * 
 * No input validation is performed -- this is not the kind of code to put
 * in production.
 */
#include <iostream>
#include <regex>
#include <string>
#include <vector>

int
main (void)
{
    struct rule {
        rule(char *re, int a, int b) : re(re), a(a), b(b) {}
        std::regex re;
        int a, b;
    };
    std::vector<rule> rules;
    std::string str;
    unsigned midNumberSum = 0;
    constexpr char *re_fmt = R"(\b(%s)\b(.*)\b(%s)\b)";
    char re_buf[64];

    while (std::getline(std::cin, str))
    {
        if (str.empty())
            break;  // Go on to the next section
        char *a, *b;
        a = (char *) str.c_str();
        b = strchr(a, '|');
        *b = '\0';
        ++b;
        /* The trick is to reverse the numbers to find the violation */
        (void) snprintf(re_buf, sizeof(re_buf), re_fmt, b, a);
        rules.emplace_back(re_buf, atoi(a), atoi(b));
    }

    while (std::getline(std::cin, str))
    {
        int commaCount, midNumber;
        const char *s;
        /* Check all rules: we only care about the bad lines */
        for (const auto &rule : rules)
            if (std::regex_search(str, rule.re))
                goto got_a_bad_one;
        continue;
got_a_bad_one:
        /* Since we are only swapping the pairs of numbers, we only care about
         * the middle number.  We need to get the string to the point until
         * the middle number does not violate any rules.  This reduces the
         * number of rules we must check.
         */
        /* Find the middle number */
        commaCount = 0;
        for (auto c : str)
            commaCount += c == ',';
recheck:
        s = str.c_str();
        for (auto i = 0; i < commaCount / 2; ++i)
            s = strchr(s, ',') + 1;
        midNumber = atoi(s);
        for (const auto &rule : rules)
        {
            if (midNumber != rule.a && midNumber != rule.b)
                continue;
            std::smatch m;
            if (std::regex_search(str, m, rule.re))
            {
                str = m.prefix().str() + std::to_string(rule.a) + m[2].str()
                    + std::to_string(rule.b) + m.suffix().str();
                goto recheck;
            }
        }
        midNumberSum += midNumber;
    }

    std::cout << midNumberSum << std::endl;
    return 0;
}
