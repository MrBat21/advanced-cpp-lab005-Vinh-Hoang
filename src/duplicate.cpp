#include "duplicate.h"

#include <unordered_set>

namespace algorithm_lab {

bool hasDuplicateNaive(const std::vector<int>& values) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        for (std::size_t j = i + 1; j < values.size(); ++j) {
            if (values[i] == values[j]) {
                return true;
            }
        }
    }
    return false;
}

bool hasDuplicateEfficient(const std::vector<int>& values) {
    std::unordered_set<int> seen;
    for (int value : values) {
        if (!seen.insert(value).second) {
            return true;
        }
    }
    return false;
}

}
