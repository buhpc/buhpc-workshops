#include <cstdint>
#include <vector>

uint64_t bench_u64ToAsciiBaseline(
    const uint64_t *nums,
    int num_tests,
    int num_iterations,
    std::vector<uint64_t> durations
);

uint64_t bench_u64ToAsciiClassic(
    const uint64_t *nums,
    int num_tests,
    int num_iterations,
    std::vector<uint64_t> durations
);

uint64_t bench_u64ToAsciiOpt(
    const uint64_t *nums,
    int num_tests,
    int num_iterations,
    std::vector<uint64_t> durations
);

uint64_t bench_u64ToAsciiTable(
    const uint64_t *nums,
    int num_tests,
    int num_iterations,
    std::vector<uint64_t> durations
);

uint64_t bench_u64ToAsciiHpc(
    const uint64_t *nums,
    int num_tests,
    int num_iterations,
    std::vector<uint64_t> durations
);
