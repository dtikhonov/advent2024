/* Day 5, part 2.  The idea is to convert the rules into regular expressions
 * and find violations that way.  Building on Part 1, we now use the offsets
 * of the matches to swap the numbers.
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
    std::vector<std::regex> rules;
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
        rules.emplace_back(re_buf);
    }

    while (std::getline(std::cin, str))
    {
        int changeCount = 0, commaCount;
restart:
        for (auto i = 0; i < rules.size(); ++i)
        {
            const auto &rule = rules[i];
            std::smatch m;
            if (std::regex_search(str, m, rule))
            {
                str = m.prefix().str() + m[3].str() + m[2].str()
                    + m[1].str() + m.suffix().str();
                ++changeCount;
                /* There has to be a better way: this is akin to a Bubble
                 * sort.  But it works.
                 */
                goto restart;
            }
        }
        if (changeCount == 0)
            continue;
        commaCount = 0;
        for (auto c : str)
            commaCount += c == ',';
        const char *s = str.c_str();
        for (auto i = 0; i < commaCount / 2; ++i)
            s = strchr(s, ',') + 1;
        midNumberSum += atoi(s);
    }

    std::cout << midNumberSum << std::endl;
    return 0;
}
