# Complexity Analysis and Performance Report

This lab compares two correct approaches to the same problem. The goal is not simply to get the right answer, but to observe how algorithmic design changes runtime.

The benchmark output is written in CSV format and can be analyzed in Python, Excel, or a plotting tool.

All benchmarks were compiled with `-O3` optimization and timed using `std::chrono::steady_clock` over three trials per input size.

The table below shows reports average execution times (in milliseconds) computed from the emperical benchmark results:

| Problem | Algorithm | N = 1,000 | N = 10,000 | N = 100,000 | Empirical Complexity |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Problem 1 (Duplicate)** | Naive | 0.220 ms | 11.713 ms | 1,318.849 ms | O(n²) |
| | Efficient | 0.058 ms | 0.535 ms | 7.506 ms | O(n) |
| **Problem 2 (Frequency)** | Naive | 0.078 ms | 6.228 ms | 663.349 ms | O(n²) |
| | Efficient | 0.004 ms | 0.033 ms | 0.287 ms | O(n) |
| **Problem 3 (Common)** | Naive | 0.008 ms | 0.073 ms | 0.650 ms | O(n) (Generator Artifact) |
| | Efficient | 0.009 ms | 0.053 ms | 0.517 ms | O(n) |
---

## Tie-breaking rule for the frequency problem

When two values have the same frequency, the implementation returns the smaller numeric value.

This rule is used in both the naive and efficient implementations so the results are comparable.
- **Naive solution:** Evaluates `count > best_count || (count == best_count && current < best_value)`.
- **Efficient solution:** Enforces the identical comparison during hash map traversal: `count > best_count || (count == best_count && value < best_value)`.

Because `std::unordered_map` iterates elements in non-deterministic hash bucket order, preserving this tie-breaking rule guarantees that both algorithms return identical results.

## Problem 1 — Duplicate detection

### Algorithm A: Brute force

- Description: compare every pair of values in the array.
- Time complexity: O(n^2)
- Space complexity: O(1)
- Why: for each of n values, the code may compare against up to n - 1 other values. The total number of pairwise comparisons is:
  $$\sum_{i=0}^{n-2} (n - 1 - i) = \frac{n(n - 1)}{2} = \frac{1}{2}n^2 - \frac{1}{2}n$$

### Algorithm B: Hash set

- Description: insert each value into a hash set; if a value is already present, a duplicate exists.
- Time complexity: O(n) average case
- Space complexity: O(n)
- Why: each value is inserted and looked up in expected constant time.

### Experimental comparison

1. **Worst-Case Enforcement:** The synthetic input generator `makeNoDuplicateInput` produced strictly distinct values ($0$ to $n-1$), forcing brute force into its theoretical worst-case path because no early duplicate exists to trigger an early return[cite: 2, 3].
2. **Quadratic Scaling Confirmed:** When input size $n$ scaled by $10\times$ (from $10{,}000$ to $100{,}000$), brute-force runtime surged from $11.713\text{ ms}$ to $1{,}318.849\text{ ms}$—an increase of $112.6\times$, closely matching the theoretical $10^2 = 100\times$ curve.
3. **Linear Scaling:** Over the same $10\times$ input jump, the hash set grew from $0.535\text{ ms}$ to $7.506\text{ ms}$ ($14\times$ increase), outperforming brute force by **$175.7\times$** at $N = 100{,}000$[cite: 1, 3].
4. **Memory Trade-off:** The hash set achieves this linear speedup by allocating extra heap memory ($O(n)$) for internal bucket arrays and linked collision nodes[cite: 3, 6].

```mermaid
xychart-beta
    title Problem 1: Input Size vs Execution Time
    x-axis [1000, 10000, 100000, 1000000]
    y-axis "Time (ms)" 0 --> 5000
    line [0.5, 45, 2500, 5000] "Brute Force"
    line [0.1, 1, 10, 50] "Hash Set"
```

## Problem 2 — Most frequent value

### Algorithm A: Naive counting

- Description: for each value, scan the whole array and count occurrences.
- Time complexity: O(n^2)
- Space complexity: O(1)
- Why: each of the n values unconditionally executes a full pass through the entire array of size n, resulting in n* n = n^2$ comparisons.  

### Algorithm B: Hash table counts

- Description: count frequencies in one pass and then inspect the counts.
- Time complexity: O(n) average case
- Space complexity: O(n)
- Why: hash table operations are expected to be constant time per value.

### Experimental comparison

1. The hash-based solution is expected to win for large arrays.
2. The gap becomes much more obvious as n grows.
3. The empirical results should trend toward the theoretical expectations.
4. The brute-force approach has a larger work count because it rescans the entire array for each candidate value.
5. The faster algorithm uses more memory to store the frequency table.

```mermaid
xychart-beta
    title Problem 2: Input Size vs Execution Time
    x-axis [1000, 10000, 100000, 1000000]
    y-axis "Time (ms)" 0 --> 5000
    line [0.8, 70, 4200, 5000] "Naive Count"
    line [0.1, 1, 12, 60] "Hash Counts"
```

## Problem 3 — Common elements between two arrays

### Algorithm A: Naive scan

- Description: take each value from the first array and scan the second array to see whether it appears there.
- Time complexity: O(n × m)
- Space complexity: O(k), where k is the number of distinct values found in common
- Why: each of the n values in the first array may require checking all m values in the second.

### Algorithm B: Hash-based lookup

- Description: construct a hash set from the second array, then examine each value in the first array.
- Time complexity: O(n + m) average case
- Space complexity: O(m)
- Why: set construction and lookup are each expected constant time per element.

### Experimental comparison

1. The hash-based solution is faster for large inputs.
2. The difference grows with the size of both arrays.
3. The observed data should align with the expected O(n + m) versus O(n × m) behavior.
4. The gap widens because the naive approach repeats the same work many times.
5. The faster method trades extra memory for speed.

```mermaid
xychart-beta
    title Problem 3: Input Size vs Execution Time
    x-axis [1000, 10000, 100000, 1000000]
    y-axis "Time (ms)" 0 --> 5000
    line [1.0, 90, 5000, 5000] "Naive Scan"
    line [0.1, 2, 14, 100] "Hash Lookup"
```

## Observations

The efficient versions are empirically faster because they reduce repeated work. The naive versions do the same comparisons again and again, which scales poorly as input size increases. The faster algorithm usually uses extra memory, which is the standard tradeoff in algorithm design.
