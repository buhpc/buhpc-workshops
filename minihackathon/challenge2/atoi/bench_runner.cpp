#include <chrono>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>

unsigned long atoul_stream(std::string numstr);
unsigned long atoul_std(const char * begin);
unsigned long atoul_O0(const char * begin, const char * end);
unsigned long atoul_O1(const char * begin, const char * end);
unsigned long atoul_O2(const char * begin, const char * end);
unsigned long atoul_hpcer(const char * begin, const char * end);

#define SHOW_TIME(var, avg) \
    std::cout << #var << " average duration was = " << \
    avg << " ns.\n"

void bench_atoul_stream(
    const std::vector<std::string> &num_strings,
    std::vector<uint64_t> &durations,
    int ITERATIONS)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        for (const auto &str : num_strings)
        {
            auto start = std::chrono::high_resolution_clock::now();
            auto result = atoul_stream(str);
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
    SHOW_TIME(atoul_stream, average);
}

void bench_atoul_std(
    const std::vector<std::string> &num_strings,
    std::vector<uint64_t> &durations,
    int ITERATIONS)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        for (const auto &str : num_strings)
        {
            // get pointers to the beginning and the end of the string
            const char * b = str.c_str();
            const char * e = &(*str.end()); //sorry for this hack :(
            
            auto start = std::chrono::high_resolution_clock::now();
            auto result = atoul_std(b);
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
    SHOW_TIME(atoul_std, average);
}

void bench_atoul_O0(
    const std::vector<std::string> &num_strings,
    std::vector<uint64_t> &durations,
    int ITERATIONS)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        for (const auto &str : num_strings)
        {
            // get pointers to the beginning and the end of the string
            const char * b = str.c_str();
            const char * e = &(*str.end()); //sorry for this hack :(
            
            auto start = std::chrono::high_resolution_clock::now();
            auto result = atoul_O0(b, e);
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
    SHOW_TIME(atoul_O0, average);
}


void bench_atoul_O1(
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
            auto result = atoul_O1(b, e);
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
    SHOW_TIME(atoul_O1, average);
}


void bench_atoul_O2(
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
            auto result = atoul_O2(b, e);
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
    SHOW_TIME(atoul_O2, average);
}
