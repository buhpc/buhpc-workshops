#include <cstdint>
#include <chrono>
#include <vector>
#include <iostream>

#define SHOW_TIME(var, avg) \
    std::cout << #var << " average duration was = " << \
    avg << " ns.\n"

uint32_t u64ToAsciiBaseline(uint64_t value, char *buffer);
uint32_t u64ToAsciiClassic(uint64_t value, char *buffer);
uint32_t u64ToAsciiOpt(uint64_t value, char *buffer);
uint32_t u64ToAsciiTable(uint64_t value, char *buffer);
uint32_t u64ToAsciiBaseline(uint64_t value, char *buffer);
uint32_t u64ToAsciiHpc(uint64_t value, char *buffer);

uint64_t bench_u64ToAsciiBaseline(
    const uint64_t *nums,
    int num_tests,
    int num_iterations,
    std::vector<uint64_t> durations
    )
{
    char buf[64];
    for (int i = 0; i < num_iterations; i++)
    {
        for (int j = 0; j < num_tests; j++)
        {            
            auto start = std::chrono::high_resolution_clock::now();
            auto result = u64ToAsciiBaseline(nums[j], buf);
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
    return total / durations.size();
}

uint64_t bench_u64ToAsciiClassic(
    const uint64_t *nums,
    int num_tests,
    int num_iterations,
    std::vector<uint64_t> durations
    )
{
    char buf[64];
    for (int i = 0; i < num_iterations; i++)
    {
        for (int j = 0; j < num_tests; j++)
        {            
            auto start = std::chrono::high_resolution_clock::now();
            auto result = u64ToAsciiClassic(nums[j], buf);
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
    return total / durations.size();
}


uint64_t bench_u64ToAsciiOpt(
    const uint64_t *nums,
    int num_tests,
    int num_iterations,
    std::vector<uint64_t> durations
    )
{
    char buf[64];
    for (int i = 0; i < num_iterations; i++)
    {
        for (int j = 0; j < num_tests; j++)
        {            
            auto start = std::chrono::high_resolution_clock::now();
            auto result = u64ToAsciiOpt(nums[j], buf);
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
    return total / durations.size();
}

uint64_t bench_u64ToAsciiTable(
    const uint64_t *nums,
    int num_tests,
    int num_iterations,
    std::vector<uint64_t> durations
    )
{
    char buf[64];
    for (int i = 0; i < num_iterations; i++)
    {
        for (int j = 0; j < num_tests; j++)
        {            
            auto start = std::chrono::high_resolution_clock::now();
            auto result = u64ToAsciiTable(nums[j], buf);
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
    return total / durations.size();
}

// no need to modify this benchmark routine
uint64_t bench_u64ToAsciiHpc(
    const uint64_t *nums,
    int num_tests,
    int num_iterations,
    std::vector<uint64_t> durations
    )
{
    char buf[64];
    for (int i = 0; i < num_iterations; i++)
    {
        for (int j = 0; j < num_tests; j++)
        {            
            auto start = std::chrono::high_resolution_clock::now();
            auto result = u64ToAsciiHpc(nums[j], buf);
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
    return total / durations.size();
}
