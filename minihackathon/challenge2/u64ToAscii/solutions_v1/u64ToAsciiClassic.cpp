#include <cstdint>
#include <iterator>


uint32_t digits10(uint64_t num)
{
    uint32_t result = 0;
    do
    {
        result++;
        num /= 10;
    } while (num > 0);

    return result;
}

uint32_t u64ToAsciiClassic(uint64_t value, char *buffer)
{
    auto start = buffer;
    do
    {
        *buffer++ = '0' + (value % 10);
        value /= 10;
    } while (value != 0);

    const uint32_t result = buffer - start;
    // Reverse in place.
    for (buffer--; buffer > start; start++, buffer--)
    {
        std::iter_swap(buffer, start);
    }

    return result;
}
