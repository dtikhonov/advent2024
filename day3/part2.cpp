#include <iostream>
#include <regex>

int
main (void)
{
    int64_t result = 0;
    bool enabled = true;
    
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::regex re(R"(\b(?:(do\(\))|(don't\(\))|mul\((\d{1,3}),(\d{1,3})\)))");
        auto begin = std::sregex_iterator(line.begin(), line.end(), re);
        auto end = std::sregex_iterator();
        for (std::sregex_iterator i = begin; i != end; ++i)
        {
            auto match = *i;
            if (match[1].matched)
                enabled = true;
            else if (match[2].matched) 
                enabled = false;
            else if (enabled)
                result += std::stoi(match[3].str()) * std::stoi(match[4].str());
        }
    }
    
    std::cout << result << std::endl;
    return 0;
}