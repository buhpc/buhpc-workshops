#include <cassert>
#include <string>

void enforce(bool);

unsigned long atoul_O2(const char * begin, const char * end)
{
    static const uint64_t pow10[20] = 
    {
        10000000000000000000UL,
        1000000000000000000UL,
        100000000000000000UL,
        10000000000000000UL,
        1000000000000000UL,
        100000000000000UL,
        10000000000000UL,
        1000000000000UL,
        100000000000UL,
        10000000000UL,
        1000000000UL,
        100000000UL,
        10000000UL,
        1000000UL,
        100000UL,
        10000UL,
        1000UL,
        100UL,
        10UL,
        1UL,
    };
    
    enforce(begin <= end);

    unsigned long result = 0;
    auto i = sizeof(pow10) / sizeof(*pow10) - (end - begin);
    for (; begin != end; ++begin)
    {
        auto digit = unsigned (*begin) - '0';
        enforce(digit < 10);
        result += pow10[i++] * digit;
    }
    return result;
}
