#include <cstdint>

uint32_t digits10_O0(uint64_t num)
{
    uint32_t result = 0;
    do
    {
        result++;
        num /= 10;
    } while (num > 0);

    return result;
}
