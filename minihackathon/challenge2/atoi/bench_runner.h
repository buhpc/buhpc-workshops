#include <vector>
#include <string>

void bench_atoul_stream(
    const std::vector<std::string> &,
    std::vector<uint64_t> &,
    int
);

void bench_atoul_std(
    const std::vector<std::string> &,
    std::vector<uint64_t> &,
    int
);

void bench_atoul_O0(
    const std::vector<std::string> &,
    std::vector<uint64_t> &,
    int
);

void bench_atoul_O1(
    const std::vector<std::string> &,
    std::vector<uint64_t> &,
    int
);

void bench_atoul_O2(
    const std::vector<std::string> &,
    std::vector<uint64_t> &,
    int
);

void bench_atoul_O3(
    const std::vector<std::string> &,
    std::vector<uint64_t> &,
    int
);