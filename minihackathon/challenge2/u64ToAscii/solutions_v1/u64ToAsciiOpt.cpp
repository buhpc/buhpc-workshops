#include <cstdint>

uint32_t digits10_O1(uint64_t num) __attribute__((__always_inline__));

uint32_t digits10_O1(uint64_t num)
{
    uint32_t result = 1;
    for (;;)
    {
        if (num < 10) return result;
        if (num < 100) return result + 1;
        if (num < 1000) return result + 2;
        if (num < 10000) return result + 3;
        num /= 10000U;
        result += 4;
    }

    return result;
}

uint32_t u64ToAsciiOpt(uint64_t num, char *const buffer)
{
    auto const result = digits10_O1(num);
    uint32_t pos = result - 1;

    while (num >= 10)
    {
        auto const q = num / 10;
        auto const r = static_cast<uint32_t>(num % 10);
        buffer[pos--] = '0' + r;
        num = q;
    }

    *buffer = static_cast<uint32_t>(num) + '0';
    return result;
}
