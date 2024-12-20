/* Day 19, Part 1 */

#include <iostream>
#include <regex>

int
main (void)
{
    /* Convert the flags into regular expression like this:
     *      "abc, xyz" -> "^(?:abc|xyz)+$"
     */
    std::string line;
    std::getline(std::cin, line);
    line = "^(?:" + std::regex_replace(line, std::regex(", "), "|") + ")+$";
    std::regex re(line);

    int count = 0;
    while (std::getline(std::cin, line))
        count += std::regex_match(line, re);

    std::cout << count << std::endl;
}
