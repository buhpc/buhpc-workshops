#include <string>
#include <cstdlib>

unsigned long atoul_std(const char *begin)
{
    return std::strtoul(begin, NULL, 10);
    /*
    unsigned long result = 0;
    unsigned int digit;
    int sign;


    while (*string == ' ') {
	string += 1;
    }


    if (*string == '-') {
	sign = 1;
	string += 1;
    } else {
	sign = 0;
	if (*string == '+') {
	    string += 1;
	}
    }

    for ( ; ; string += 1) {
	digit = *string - '0';
	if (digit > 9) {
	    break;
	}
	result = (10*result) + digit;
    }

    if (sign) {
	return -result;
    }
    return result;
    */
}