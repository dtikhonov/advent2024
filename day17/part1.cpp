/* Day 17, Part 1 */

#include <regex>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

enum op {
    op_adv = 00,    // Divide register A
    op_bxl = 01,    // XOR B
    op_bst = 02,    // Modulo 8 -> B
    op_jnz = 03,    // Jump if A is not zero
    op_bxc = 04,    // B ^ C -> B
    op_out = 05,    // Output modulo 8
    op_bdv = 06,    // Divide register B
    op_cdv = 07,    // Divide register C
};

static const char *const op_names[8] = {
    "ADV", "BXL", "BST", "JNZ", "BXC", "OUT", "BDV", "CDV"
};

enum { A, B, C, };   // Registers

using anyinteger_t = unsigned;

struct state
{
    anyinteger_t R[3];
    std::vector<std::pair<enum op, unsigned>> program;
};

static anyinteger_t
getCombo (const struct state &st, unsigned operand)
{
    if (operand < 4)
        return operand;
    else if (operand < 7)
        return st.R[operand - 4];
    else
    {
        std::cerr << "Invalid operand: " << operand << std::endl;
        return 0;
    }
}

int
main (int argc, char **argv)    // Usage prog debug < input.txt
{
    const bool DEBUG = argc > 1 && std::string(argv[1]) == "debug";
    struct state st;

    std::string line;
    while (std::getline(std::cin, line))
    {
        char reg;
        anyinteger_t v;
        if (std::sscanf(line.c_str(), "Register %c: %u", &reg, &v))
            st.R[reg - 'A'] = v;
        else if (line.find("Program: ", 0) == 0)
        {
            std::regex re = std::regex("([0-9]+),([0-9]+)");
            auto begin = std::sregex_iterator(line.begin(), line.end(), re);
            auto end = std::sregex_iterator();
            for (std::sregex_iterator i = begin; i != end; ++i)
                st.program.push_back({
                    static_cast<enum op>(std::stoi((*i)[1].str())),
                    std::stoi((*i)[2].str())
                });
        }
    }

    unsigned ip = 0, needComma = 0;
    while (ip < st.program.size())
    {
        const auto &[op, arg] = st.program[ip];
        if (DEBUG)
        {
            std::cout << "ip: " << ip << " " << op_names[op] << " " << arg << "\n";
            std::cout << "R[A]: " << st.R[A] << " R[B]: " << st.R[B] << " R[C]: " << st.R[C] << "\n";
        }
        switch (op)
        {
            case op_adv:
                st.R[A] = st.R[A] / (1u << getCombo(st, arg));
                break;
            case op_bxl:
                st.R[B] = st.R[B] ^ arg;
                break;
            case op_bst:
                st.R[B] = getCombo(st, arg) % 8;
                break;
            case op_jnz:
                if (st.R[A] != 0)
                {
                    ip = arg / 1;
                    continue;
                }
                break;
            case op_bxc:
                st.R[B] = st.R[B] ^ st.R[C];
                break;
            case op_out:
                if (needComma++)
                    std::cout << ',';
                std::cout << getCombo(st, arg) % 8;
                if (DEBUG)
                    std::cout << "\n";
                break;
            case op_bdv:
                st.R[B] = st.R[A] / (1u << getCombo(st, arg));
                break;
            case op_cdv:
                st.R[C] = st.R[A] / (1u << getCombo(st, arg));
                break;
        }
        ip += 1;
    }

    if (needComma)
        std::cout << std::endl;

    return 0;
}