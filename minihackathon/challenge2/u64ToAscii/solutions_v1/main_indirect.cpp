#include <vector>
#include <chrono>
#include <numeric>
#include <cstdint>
#include <iostream>
#include "bench_runner.h"
#include "Benchmark.h"

uint32_t u64ToAsciiBaseline(uint64_t value, char *buffer);
uint32_t u64ToAsciiClassic(uint64_t value, char *buffer);
uint32_t u64ToAsciiOpt(uint64_t value, char *buffer);
uint32_t u64ToAsciiTable(uint64_t value, char *buffer);
uint32_t u64ToAsciiBaseline(uint64_t value, char *buffer);
uint32_t u64ToAsciiHpc(uint64_t value, char *buffer);

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
        999999, 9999999, 99999999, 999999999,
        9999999999, 99999999999, 999999999999,
        9999999999999, 99999999999999,9999999999999,
        999999999999999, 99999999999999999
    };

    auto benchmark = Benchmark{NUM_TESTS, NUM_ITERATIONS, nums};
    benchmark.warmup_cache();
    
    // baseline
    auto avg_baseline = benchmark.run(u64ToAsciiBaseline);
    SHOW_TIME(u64ToAsciiBaseline, avg_baseline);

    // reference implementation
    auto avg_classic = benchmark.run(u64ToAsciiClassic);
    SHOW_TIME(u64ToAsciiClassic, avg_classic - avg_baseline);

    // first optimization level
    auto avg_opt = benchmark.run(u64ToAsciiClassic);
    SHOW_TIME(u64ToAsciiOpt, avg_opt - avg_baseline);

    // second optimization level
    auto avg_table = benchmark.run(u64ToAsciiTable);
    SHOW_TIME(u64ToAsciiTable, avg_table - avg_baseline);

#ifdef I_ACCEPT_THE_MISSION
    auto avg_hpc = benchmark.run(u64ToAsciiHpc);
    SHOW_TIME(u64ToAsciiHpc, avg_hpc - avg_baseline);
#endif

    return 0;
}
