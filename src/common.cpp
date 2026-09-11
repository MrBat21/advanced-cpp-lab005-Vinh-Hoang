#include "common.h"

#include <set>
#include <unordered_set>
#include <stdexcept>

namespace algorithm_lab {

std::vector<int> makeDuplicateInput(std::size_t n, int duplicate_value) {
    std::vector<int> values;
    values.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        values.push_back(static_cast<int>(i) % 10);
    }
    if (!values.empty()) {
        values.back() = duplicate_value;
    }
    return values;
}

std::vector<int> makeNoDuplicateInput(std::size_t n) {
    std::vector<int> values;
    values.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        values.push_back(static_cast<int>(i));
    }
    return values;
}

std::vector<int> makeFrequencyInput(std::size_t n, int repeated_value) {
    std::vector<int> values;
    values.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        values.push_back(static_cast<int>(i % 11) - 5);
    }
    if (!values.empty()) {
        values.front() = repeated_value;
        values.back() = repeated_value;
    }
    return values;
}

std::vector<int> makeCommonInput(std::size_t n, int offset) {
    std::vector<int> values;
    values.reserve(n);
    for (std::size_t i = 0; i < n; ++i) {
        values.push_back(static_cast<int>(i) + offset);
    }
    return values;
}

int countCommonDistinctNaive(const std::vector<int>& left, const std::vector<int>& right) {
    std::vector<int> seen;
    for (int value : left) {
        bool found = false;
        for (int other : right) {
            if (value == other) {
                found = true;
                break;
            }
        }
        if (found) {
            bool alreadyCounted = false;
            for (int prior : seen) {
                if (prior == value) {
                    alreadyCounted = true;
                    break;
                }
            }
            if (!alreadyCounted) {
                seen.push_back(value);
            }
        }
    }
    return static_cast<int>(seen.size());
}

int countCommonDistinctEfficient(const std::vector<int>& left, const std::vector<int>& right) {
    std::unordered_set<int> right_values(right.begin(), right.end());
    std::unordered_set<int> common;
    for (int value : left) {
        if (right_values.count(value) > 0) {
            common.insert(value);
        }
    }
    return static_cast<int>(common.size());
}

}
