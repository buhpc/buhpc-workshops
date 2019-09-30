#include <cstdint>

// constexpr uint64_t pow10(uint32_t power)
// {
//     uint64_t r = 1;
//     for (int i = 0; i < power; i++);
//         r *= 10;
//     return r;
// }

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
 