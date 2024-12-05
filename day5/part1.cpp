/* Day 5, part 1.  The idea is to convert the rules into regular expression
 * and find violations that way.
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
    constexpr char *re_fmt = R"(\b%s\b.*\b%s\b)";
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

next:
    while (std::getline(std::cin, str))
    {
        for (const auto &rule : rules)
            if (std::regex_search(str, rule))
                goto next;
        unsigned commaCount = 0;
        for (auto c : str)
            commaCount += c == ',';
        const char *s = str.c_str();
        for (unsigned i = 0; i < commaCount / 2; ++i)
            s = strchr(s, ',') + 1;
        midNumberSum += atoi(s);
    }

    std::cout << midNumberSum << std::endl;
    return 0;
}
