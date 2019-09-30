#include <cstdint>

uint32_t digits10_O1(uint64_t num)
{
    uint32_t result = 1;
    for (;;)
    {
        if (num < 10) return result;
        if (num < 100) return result + 1;
        if (num < 1000) return result + 2;
        if (num < 10000) return result + 3;
        // Skip ahead by 4 orders of magnitude
        num /= 10000U;
        result += 4;
    }

    return result;
}
