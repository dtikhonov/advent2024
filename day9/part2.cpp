/* Day 9, Part 2 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <list>

struct obj  // Either file or empty space
{
    unsigned off;
    unsigned len;
    int file_id;    // -1 means empty space
};

int
main (void)
{
    std::list<obj> objs;
    std::string in;

    enum state { FILE, FREE } state = FILE;
    int file_id = 0;

    (void) std::getline(std::cin, in);

    unsigned off = 0;
    for (auto c : in)
    {
        const unsigned len = c - '0';
        objs.push_back({off, len, state == FILE ? file_id++ : -1});
        off += len;
        state = static_cast<enum state>(1 & (state + 1));
    }

    for (auto it = objs.rbegin(); it != objs.rend(); ++it)
    {
        auto &file = *it;
        if (file.file_id < 0)
            continue;   // Not a file
        auto empty_it = std::find_if(objs.begin(), objs.end(),
            [&file](const obj &obj)
            {
                return obj.file_id < 0
                    && obj.off < file.off
                    && obj.len >= file.len
                    ;
            });
        if (empty_it == objs.end())
            continue;
        auto &empty = *empty_it;
        if (empty.len == file.len)
            /* A perfect fit: simply replace empty space with the file */
            empty.file_id = file.file_id;
        else
        {
            /* Front part of the empty space is used by the file */
            empty.len -= file.len;
            empty.off += file.len;
            /* Insert file before empty space */
            objs.insert(empty_it, {empty.off - file.len, file.len, file.file_id});
        }
        file.file_id = -1;  // File is now empty space
    }
    
    uint64_t sum = 0;
    for (const auto &obj : objs)
        if (obj.file_id >= 0)
            for (auto n = obj.off; n < obj.off + obj.len; ++n)
                sum += n * obj.file_id;

    std::cout << sum << "\n";

    return 0;
}
