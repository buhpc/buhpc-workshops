#include <string>
#include <sstream>

unsigned long atoul_stream(std::string numstr)
{
    auto stream = std::stringstream{numstr};
    unsigned long result = 0;
    stream >> result;
    return result;
}
