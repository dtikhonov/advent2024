#include <iostream>
#include <regex>

int
main (void)
{
    int64_t result = 0;
    
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::regex re(R"(\bmul\((\d{1,3}),(\d{1,3})\))");
        auto begin = std::sregex_iterator(line.begin(), line.end(), re);
        auto end = std::sregex_iterator();
        for (std::sregex_iterator i = begin; i != end; ++i)
        {
            auto match = *i;
            result += std::stoi(match[1].str()) * std::stoi(match[2].str());
        }
    }
    
    std::cout << result << std::endl;
    return 0;
}