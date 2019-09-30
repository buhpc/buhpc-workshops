#include <vector>
#include <chrono>
#include <numeric>
#include <cstdint>
#include <iostream>
#include "bench_runner.h"

uint64_t warmup_cache(const uint64_t *, const std::vector<uint64_t> &);

// number of iterations for the bechmark
#define NUM_ITERATIONS 100000
#define NUM_TESTS 17
#define SHOW_TIME(func, avg) \
    std::cout << #func << " average duration was = " << avg << " ns.\n"

// START HERE: YOUR MISSION, SHOULD YOU CHOOSE TO ACCEPT IT
#define I_ACCEPT_THE_MISSION

int main(int argc, char const *argv[])
{
    const uint64_t nums[NUM_TESTS]
    {
        9, 99, 999, 9999, 99999,
        999999, 9999999, 99999999, 
        999999999, 9999999999, 99999999999,
        999999999999, 9999999999999, 99999999999999,
        9999999999999, 999999999999999, 99999999999999999
    };

    // bookkeeping and some normalization
    std::vector<uint64_t> durations;
    durations.reserve(NUM_ITERATIONS * NUM_TESTS);
    warmup_cache(nums, durations);

    // baseline
    auto avg_baseline = bench_u64ToAsciiBaseline(nums, NUM_TESTS, NUM_ITERATIONS, durations);
    durations.clear();
    durations.reserve(NUM_ITERATIONS * NUM_TESTS);
    SHOW_TIME(u64ToAsciiBaseline, avg_baseline);

    // reference implementation
    auto avg_classic = bench_u64ToAsciiClassic(nums, NUM_TESTS, NUM_ITERATIONS, durations);
    durations.clear();
    durations.reserve(NUM_ITERATIONS * NUM_TESTS);
    SHOW_TIME(u64ToAsciiClassic, avg_classic - avg_baseline);

    auto avg_opt = bench_u64ToAsciiOpt(nums, NUM_TESTS, NUM_ITERATIONS, durations);
    durations.clear();
    durations.reserve(NUM_ITERATIONS * NUM_TESTS);
    SHOW_TIME(u64ToAsciiOpt, avg_opt - avg_baseline);

    auto avg_table = bench_u64ToAsciiTable(nums, NUM_TESTS, NUM_ITERATIONS, durations);
    durations.clear();
    durations.reserve(NUM_ITERATIONS * NUM_TESTS);
    SHOW_TIME(u64ToAsciiTable, avg_table - avg_baseline);

#ifdef I_ACCEPT_THE_MISSION
    auto avg_hpc = bench_u64ToAsciiHpc(nums, NUM_TESTS, NUM_ITERATIONS, durations);
    durations.clear();
    durations.reserve(NUM_ITERATIONS * NUM_TESTS);
    SHOW_TIME(u64ToAsciiHpc, avg_hpc - avg_baseline);
#endif

    return 0;
}

uint64_t warmup_cache(
    const uint64_t *nums,
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
