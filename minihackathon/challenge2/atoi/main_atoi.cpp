#include <string>
#include <vector>
#include <chrono>
#include <cstring>
#include <numeric>
#include <algorithm>
#include "bench_runner.h"

uint64_t warmup_cache(const std::vector<std::string> &, const std::vector<uint64_t> &);

// number of iterations for the bechmark
#define NUM_ITERATIONS 100000
#define SHOW_TIME(var, avg) \
    std::cout << #var << " average duration was = " << \
    avg << " ns.\n"

// bechmark data
#ifdef I_ACCEPT_THE_MISSION 
    unsigned long atoul_hacker(const char * begin, const char * end);
#endif

int main(int argc, char const *argv[])
{
    const std::vector<std::string> num_strings = 
    {
        "9","99","999","9999","99999",
        "999999", "9999999", "99999999", 
        "999999999", "9999999900", "99999999999",
        "999999999999", "9999999999999", "99999999999999"
    };

    // bookkeeping and some normalization
    std::vector<uint64_t> durations;
    durations.reserve(NUM_ITERATIONS * num_strings.size());
    warmup_cache(num_strings, durations);

    // stream based typecast
    bench_atoul_stream(num_strings, durations, NUM_ITERATIONS);
    durations.clear();
    durations.reserve(NUM_ITERATIONS * num_strings.size());

    // stdlib implementation
    bench_atoul_std(num_strings, durations, NUM_ITERATIONS);
    durations.clear();
    durations.reserve(NUM_ITERATIONS * num_strings.size());

    // reference implementation that you have to optimize
    bench_atoul_O0(num_strings, durations, NUM_ITERATIONS);
    durations.clear();
    durations.reserve(NUM_ITERATIONS * num_strings.size());

    // hand optimized solution
    bench_atoul_O1(num_strings, durations, NUM_ITERATIONS);
    durations.clear();
    durations.reserve(NUM_ITERATIONS * num_strings.size());

    // ... and more hand optimized
    bench_atoul_O2(num_strings, durations, NUM_ITERATIONS);
    durations.clear();
    durations.reserve(NUM_ITERATIONS * num_strings.size());

#ifdef I_ACCEPT_THE_MISSION
    bench_atoul_hpcer(num_strings, durations, NUM_ITERATIONS);
    durations.clear();
    durations.reserve(NUM_ITERATIONS * num_strings.size());
#endif

    return 0;
}


#ifdef I_ACCEPT_THE_MISSION
unsigned long 
atoul_hpcer(const char * begin, const char * end)
{
    auto result = 0ULL;
    // TODO: INSERT YOUR CODE HERE
    return result;
}

void bench_atoul_hpcer(
    const std::vector<std::string> &num_strings,
    std::vector<uint64_t> &durations,
    int ITERATIONS
)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        for (const auto &str : num_strings)
        {
            // get pointers to the beginning and the end of the string
            const char * b = str.c_str();
            const char * e = &(*str.end()); //sorry for this hack :(
            
            auto start = std::chrono::high_resolution_clock::now();
            auto result = atoul_hpcer(b, e);
            auto end = std::chrono::high_resolution_clock::now();

            // save the measured duration
            durations.emplace_back(
                (std::chrono::duration_cast<std::chrono::nanoseconds>(end - start))
                    .count()
            );
        }
    }

    auto total = 0ULL;
    for (const auto &d : durations) total += d;
    auto average = total / durations.size();
    SHOW_TIME(atoul_hpcer, average);
}
#endif

uint64_t warmup_cache(
    const std::vector<std::string> & num_strings,
    const std::vector<uint64_t> &durations)
{
    auto len = 0ULL;
    for (auto &str : num_strings)
    {
        len += std::strlen(str.c_str());
    }

    for (auto &d: durations) len += d;
    return len;
}
