#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <vector>

#include "common.h"
#include "duplicate.h"
#include "frequency.h"

namespace {

using Clock = std::chrono::steady_clock;

std::vector<int> buildDuplicateBenchmarkInput(std::size_t n) {
    return algorithm_lab::makeNoDuplicateInput(n);
}

std::vector<int> buildFrequencyBenchmarkInput(std::size_t n) {
    std::vector<int> values;
    values.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        values.push_back(static_cast<int>(i % 7) - 3);
    }
    values.back() = -3;
    return values;
}

std::vector<int> buildCommonBenchmarkLeft(std::size_t n) {
    std::vector<int> values;
    values.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        values.push_back(static_cast<int>(i) % 19);
    }
    return values;
}

std::vector<int> buildCommonBenchmarkRight(std::size_t n) {
    std::vector<int> values;
    values.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        values.push_back(static_cast<int>(i * 13) % 19);
    }
    return values;
}

long long measure_ns(const std::function<void()>& fn) {
    auto start = Clock::now();
    fn();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - start).count();
}

void emit_csv_row(const std::string& problem, const std::string& algorithm,
                  std::size_t input_size, int trial, long long nanoseconds) {
    std::cout << problem << ',' << algorithm << ',' << input_size << ',' << trial << ',' << nanoseconds << '\n';
}

void benchmark_duplicate(std::size_t max_input_size, int trials) {
    for (std::size_t n : {1000UL, 10000UL, 100000UL, 1000000UL}) {
        if (n > max_input_size) {
            continue;
        }

        auto data = buildDuplicateBenchmarkInput(n);
        for (int trial = 1; trial <= trials; ++trial) {
            auto naive_ns = measure_ns([&]() {
                volatile bool result = algorithm_lab::hasDuplicateNaive(data);
                (void)result;
            });
            emit_csv_row("duplicate", "naive", n, trial, naive_ns);

            auto efficient_ns = measure_ns([&]() {
                volatile bool result = algorithm_lab::hasDuplicateEfficient(data);
                (void)result;
            });
            emit_csv_row("duplicate", "efficient", n, trial, efficient_ns);
        }
    }
}

void benchmark_frequency(std::size_t max_input_size, int trials) {
    for (std::size_t n : {1000UL, 10000UL, 100000UL, 1000000UL}) {
        if (n > max_input_size) {
            continue;
        }

        auto data = buildFrequencyBenchmarkInput(n);
        for (int trial = 1; trial <= trials; ++trial) {
            auto naive_ns = measure_ns([&]() {
                volatile int result = algorithm_lab::mostFrequentNaive(data);
                (void)result;
            });
            emit_csv_row("frequency", "naive", n, trial, naive_ns);

            auto efficient_ns = measure_ns([&]() {
                volatile int result = algorithm_lab::mostFrequentEfficient(data);
                (void)result;
            });
            emit_csv_row("frequency", "efficient", n, trial, efficient_ns);
        }
    }
}

void benchmark_common(std::size_t max_input_size, int trials) {
    for (std::size_t n : {1000UL, 10000UL, 100000UL, 1000000UL}) {
        if (n > max_input_size) {
            continue;
        }

        auto left = buildCommonBenchmarkLeft(n);
        auto right = buildCommonBenchmarkRight(n);
        for (int trial = 1; trial <= trials; ++trial) {
            auto naive_ns = measure_ns([&]() {
                volatile int result = algorithm_lab::countCommonDistinctNaive(left, right);
                (void)result;
            });
            emit_csv_row("common", "naive", n, trial, naive_ns);

            auto efficient_ns = measure_ns([&]() {
                volatile int result = algorithm_lab::countCommonDistinctEfficient(left, right);
                (void)result;
            });
            emit_csv_row("common", "efficient", n, trial, efficient_ns);
        }
    }
}

}  // namespace

int main(int argc, char** argv) {
    std::size_t max_input_size = 100000UL;
    int trials = 3;

    if (argc >= 2) {
        max_input_size = static_cast<std::size_t>(std::stoul(argv[1]));
    }
    if (argc >= 3) {
        trials = std::stoi(argv[2]);
    }

    std::cout << "problem,algorithm,input_size,trial,time_ns\n";
    benchmark_duplicate(max_input_size, trials);
    benchmark_frequency(max_input_size, trials);
    benchmark_common(max_input_size, trials);
    return 0;
}
