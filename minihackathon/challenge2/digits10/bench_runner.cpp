#include <cstdint>
#include <vector>
#include <chrono>
#include <iostream>

uint32_t digits10_O0(uint64_t);
uint32_t digits10_O1(uint64_t);
uint32_t digits10_O2(uint64_t);

#define SHOW_TIME(var, avg) \
    std::cout << #var << " average duration was = " << \
    avg << " ns.\n"

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
            auto result = digits10_O0(nums[j]);
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
    SHOW_TIME(digits10_O0, average);
}


void bench_digits10_O1(
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
            auto result = digits10_O1(nums[j]);
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
    SHOW_TIME(digits10_O1, average);
}


void bench_digits10_O2(
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
            auto result = digits10_O2(nums[j]);
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
    SHOW_TIME(digits10_O2, average);
}
