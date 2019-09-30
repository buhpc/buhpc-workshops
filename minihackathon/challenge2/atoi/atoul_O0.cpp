#include <cassert>
#include <string>

void enforce(bool);

unsigned long atoul_O0(const char * begin, const char * end)
{
    enforce(begin <= end);
    unsigned long result = 0;

    for (; begin != end; ++begin)
    {
        enforce(*begin >= '0' && *begin <= '9');
        result = result * 10 + (*begin - '0');
    }

    return result;
}

void enforce(bool condition)
{
    if (!condition)
        throw std::string("oof");
}