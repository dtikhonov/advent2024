/* Day 9, Part 1 */
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int
main (void)
{
    std::string in;
    std::vector<int64_t> out;   // -1 means empty space

    enum state { FILE, FREE } state = FILE;
    int64_t file_id = 0;

    (void) std::getline(std::cin, in);

    /* Step one: generate the 00...111...2...333.44.5555.6666.777.888899 form */
    for (auto c : in)
    {
        switch (state)
        {
        case FILE:
            for (int i = c - '0'; i > 0; --i)
                out.push_back(file_id);
            ++file_id;
            break;
        default:
            for (int i = c - '0'; i > 0; --i)
                out.push_back(-1);
            break;
        }
        state = static_cast<enum state>(1 & (state + 1));
    }

    /* Step 2: rearrange to 0099811188827773336446555566.............. form */
    size_t dst_idx = 0, src_idx = out.size() - 1;
    while (true)
    {
        while (out[dst_idx] != -1 && dst_idx <= src_idx)
            ++dst_idx;
        while (out[src_idx] == -1 && src_idx >= dst_idx)
            --src_idx;
        if (dst_idx < src_idx)
            std::swap(out[dst_idx++], out[src_idx--]);
        else
            break;
    }

    /* Step 3: perform the calculation */
    uint64_t sum = 0;
    for (size_t i = 0; i < out.size() && out[i] >= 0; ++i)
        sum += i * out[i];

    std::cout << sum << "\n";
    return 0;
}
