#include <vector>
#include <chrono>
#include <numeric>
#include <cstdint>
#include "bench_runner.h"

uint64_t warmup_cache(const uint64_t *, const std::vector<uint64_t> &);

// number of iterations for the bechmark
#define NUM_ITERATIONS 1000000
#define NUM_TESTS 17
#define SHOW_TIME(var, avg) \
    std::cout << #var << " average duration was = " << \
    avg << " ns.\n"

// START HERE: YOUR MISSION< SHOULD YOU CHOOSE TO ACCEPT IT
#ifdef I_ACCEPT_THE_MISSION 
    uint32_t digits10_hpcer(uint64_t);
    void bench_digits10_hpcer()
#endif

int main(int argc, char const *argv[])
{
    const uint64_t nums[NUM_TESTS]
    {
        9, 99, 999, 9999, 99999,
        999999, 9999999, 99999999, 
        999999999, 9999999900, 99999999999,
        999999999999, 9999999999999, 99999999999999,
        999999999999, 9999999999999, 99999999999999
    };

    // bookkeeping and some normalization
    std::vector<uint64_t> durations;
    durations.reserve(NUM_ITERATIONS * NUM_TESTS);
    warmup_cache(nums, durations);

    // reference digits10 function
    bench_digits10_O0(nums, NUM_TESTS, NUM_ITERATIONS, durations);
    durations.clear();
    durations.reserve(NUM_ITERATIONS * NUM_TESTS);
    
    // optimized one
    bench_digits10_O1(nums, NUM_TESTS, NUM_ITERATIONS, durations);
    durations.clear();
    durations.reserve(NUM_ITERATIONS * NUM_TESTS);

    // optimized one
    bench_digits10_O2(nums, NUM_TESTS, NUM_ITERATIONS, durations);
    durations.clear();
    durations.reserve(NUM_ITERATIONS * NUM_TESTS);

#ifdef I_ACCEPT_THE_MISSION
    bench_atoul_hpcer(num_strings, durations, NUM_ITERATIONS, durations);
    durations.clear();
    durations.reserve(NUM_ITERATIONS * NUM_TESTS);
#endif

    return 0;
}

#ifdef I_ACCEPT_THE_MISSION
uint32_t 
digits10_hpcer(const char * begin, const char * end)
{
    auto result = 0ULL;
    // TODO: INSERT YOUR CODE HERE
    return result;
}

void bench_digits10_O0(
    const uint64_t *nums,
    int num_tests,
    int num_iterations,
    std::vector<uint64_t> durations
    )
{
    for (int i = 0; i < num_iterations; i++)
    {
        for (int j = 0; j < num_tests; j++)
        {            
            auto start = std::chrono::high_resolution_clock::now();
            auto result = digits10_hpcer(nums[j]);
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
    SHOW_TIME(digits10_hpcer, average);
}
#endif

uint64_t warmup_cache(
    const uint64_t * nums,
    const std::vector<uint64_t> &durations)
{
    auto len = 0ULL;
    for (int i = 0; i < NUM_TESTS; i++)
    {
        len += nums[i];
    }

    for (auto &d: durations) len += d;
    return len;
}
