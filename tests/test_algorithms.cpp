#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "common.h"
#include "duplicate.h"
#include "frequency.h"

#include <chrono>
#include <vector>

using namespace algorithm_lab;

namespace {
using Clock = std::chrono::steady_clock;

template <typename Func>
long long measureNanoseconds(Func&& func) {
    auto start = Clock::now();
    func();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - start).count();
}
}

TEST_CASE("Duplicate detection returns matching answers") {
    REQUIRE(hasDuplicateNaive({}) == false);
    REQUIRE(hasDuplicateEfficient({}) == false);
    REQUIRE(hasDuplicateNaive({7}) == false);
    REQUIRE(hasDuplicateEfficient({7}) == false);
    REQUIRE(hasDuplicateNaive({1, 2, 3, 4, 5}) == false);
    REQUIRE(hasDuplicateEfficient({1, 2, 3, 4, 5}) == false);
    REQUIRE(hasDuplicateNaive({3, 1, 3, 2, 5}) == true);
    REQUIRE(hasDuplicateEfficient({3, 1, 3, 2, 5}) == true);
    REQUIRE(hasDuplicateNaive({-5, -5, 0, 2}) == true);
    REQUIRE(hasDuplicateEfficient({-5, -5, 0, 2}) == true);

    std::vector<int> large = makeNoDuplicateInput(3000);
    large.back() = 42;
    REQUIRE(hasDuplicateNaive(large) == true);
    REQUIRE(hasDuplicateEfficient(large) == true);
}

TEST_CASE("Duplicate detection should be measurably faster with the efficient algorithm") {
    auto large = makeNoDuplicateInput(20000);
    long long naive_ns = measureNanoseconds([&]() {
        volatile bool result = hasDuplicateNaive(large);
        (void)result;
    });
    long long efficient_ns = measureNanoseconds([&]() {
        volatile bool result = hasDuplicateEfficient(large);
        (void)result;
    });

    REQUIRE(hasDuplicateNaive(large) == false);
    REQUIRE(hasDuplicateEfficient(large) == false);
    REQUIRE(naive_ns > efficient_ns * 5);
}

TEST_CASE("Most frequent value matches in both implementations") {
    REQUIRE(mostFrequentNaive({1, 2, 3, 4}) == 1);
    REQUIRE(mostFrequentEfficient({1, 2, 3, 4}) == 1);
    REQUIRE(mostFrequentNaive({5, 5, 5, 5}) == 5);
    REQUIRE(mostFrequentEfficient({5, 5, 5, 5}) == 5);
    REQUIRE(mostFrequentNaive({3, 1, 3, 2, 1, 3}) == 3);
    REQUIRE(mostFrequentEfficient({3, 1, 3, 2, 1, 3}) == 3);
    REQUIRE(mostFrequentNaive({2, 1, 1, 2, 3, 4, 4}) == 1);
    REQUIRE(mostFrequentEfficient({2, 1, 1, 2, 3, 4, 4}) == 1);
    REQUIRE(mostFrequentNaive({-3, -3, -1, -1, -1}) == -1);
    REQUIRE(mostFrequentEfficient({-3, -3, -1, -1, -1}) == -1);

    std::vector<int> large = makeFrequencyInput(5000, -2);
    REQUIRE(mostFrequentNaive(large) == mostFrequentEfficient(large));
}

TEST_CASE("Most frequent value should be faster with the hash-based approach") {
    auto large = makeFrequencyInput(20000, -7);
    long long naive_ns = measureNanoseconds([&]() {
        volatile int result = mostFrequentNaive(large);
        (void)result;
    });
    long long efficient_ns = measureNanoseconds([&]() {
        volatile int result = mostFrequentEfficient(large);
        (void)result;
    });

    REQUIRE(mostFrequentNaive(large) == mostFrequentEfficient(large));
    REQUIRE(naive_ns > efficient_ns * 5);
}

TEST_CASE("Common distinct element count matches in both implementations") {
    REQUIRE(countCommonDistinctNaive({1, 2, 3}, {3, 4, 5}) == 1);
    REQUIRE(countCommonDistinctEfficient({1, 2, 3}, {3, 4, 5}) == 1);
    REQUIRE(countCommonDistinctNaive({1, 2, 2, 3}, {2, 2, 4, 5}) == 1);
    REQUIRE(countCommonDistinctEfficient({1, 2, 2, 3}, {2, 2, 4, 5}) == 1);
    REQUIRE(countCommonDistinctNaive({}, {}) == 0);
    REQUIRE(countCommonDistinctEfficient({}, {}) == 0);

    auto left = makeCommonInput(2000, 10);
    auto right = makeCommonInput(2000, 1000);
    left[1500] = 42;
    right[1700] = 42;
    REQUIRE(countCommonDistinctNaive(left, right) == countCommonDistinctEfficient(left, right));
}

TEST_CASE("Common-element search should be measurably faster with the efficient algorithm") {
    auto left = makeCommonInput(15000, 0);
    auto right = makeCommonInput(15000, 7000);

    long long naive_ns = measureNanoseconds([&]() {
        volatile int result = countCommonDistinctNaive(left, right);
        (void)result;
    });
    long long efficient_ns = measureNanoseconds([&]() {
        volatile int result = countCommonDistinctEfficient(left, right);
        (void)result;
    });

    REQUIRE(countCommonDistinctNaive(left, right) == countCommonDistinctEfficient(left, right));
    REQUIRE(naive_ns > efficient_ns * 3);
}
