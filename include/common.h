#pragma once

#include <vector>

namespace algorithm_lab {
std::vector<int> makeDuplicateInput(std::size_t n, int duplicate_value = 42);
std::vector<int> makeNoDuplicateInput(std::size_t n);
std::vector<int> makeFrequencyInput(std::size_t n, int repeated_value = 7);
std::vector<int> makeCommonInput(std::size_t n, int offset = 100);
int countCommonDistinctNaive(const std::vector<int>& left, const std::vector<int>& right);
int countCommonDistinctEfficient(const std::vector<int>& left, const std::vector<int>& right);
}
