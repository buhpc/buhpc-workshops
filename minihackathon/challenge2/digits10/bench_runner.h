#pragma once

#include <cstdint>
#include <vector>

void bench_digits10_O0(
    const uint64_t *nums,
    int num_tests,
    int num_iterations,
    std::vector<uint64_t> durations
);

void bench_digits10_O1(
    const uint64_t *nums,
    int num_tests,
    int num_iterations,
    std::vector<uint64_t> durations
);

void bench_digits10_O2(
    const uint64_t *nums,
    int num_tests,
    int num_iterations,
    std::vector<uint64_t> durations
);
