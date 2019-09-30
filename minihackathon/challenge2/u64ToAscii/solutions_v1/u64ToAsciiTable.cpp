#include <cstdint>

uint32_t digits10_O2(uint64_t num)
{
  if (num < 10ull) return 1;
  if (num < 100ull) return 2;
  if (num < 1000ull) return 3;

    if (num < 1000000000000ull)
    {
        if (num < 100000000ull)
        {
            if (num < 1000000ull)
            {
                if (num < 10000ull)
                    return 4;
                else
                    return 5 + (num >= 100000ull);
            }
            else
            {
                return 7 + (num >= 10000000ull);
            }
        }
        if (num < 10000000000ull)
        {
            return 9 + (num >= 1000000000ull);
        }
        else
        {
            return 11 + (num >= 100000000000ull);
        }
    }

    return 12 + digits10_O2(num / 1000000000000ull);
}

uint32_t u64ToAsciiTable(uint64_t value, char *buf)
{
    static const char digits[201] =
    "0001020304050607080910111213141516171819"
    "2021222324252627282930313233343536373839"
    "4041424344454647484950515253545556575859"
    "6061626364656667686970717273747576777879"
    "8081828384858687888990919293949596979899";

    uint32_t const length = digits10_O2(value);
    uint32_t next = length - 1;

    while (value >= 100)
    {
        auto const i = (value % 100) * 2;
        value /= 100;
        buf[next] = digits[i + 1];
        buf[next - 1] = digits[i];
        next -= 2;
    }

    // Handle last 1-2 digits
    if (value < 10)
    {
        buf[next] = '0' + uint32_t(value);
    }
    else
    {
        auto i = uint32_t(value) * 2;
        buf[next] = digits[i + 1];
        buf[next - 1] = digits[i];
    }

    return length;
}
