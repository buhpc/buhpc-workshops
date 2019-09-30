#include <cstdint>
#include <iterator>
#include <string>
#include <sstream>
#include <cstdlib>

uint32_t u64ToAsciiStream(uint64_t value, char *buffer)
{

    std::stringstream ss;
    ss << value;
    auto val_str = ss.str();
    auto val_cstr = val_str.c_str();
    std::strcpy(buffer, val_cstr);
    return val_str.length();
}
