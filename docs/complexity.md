# Complexity Analysis and Performance Report

This lab compares two correct approaches to the same problem. The goal is not simply to get the right answer, but to observe how algorithmic design changes runtime.

The benchmark output is written in CSV format and can be analyzed in Python, Excel, or a plotting tool.

## Tie-breaking rule for the frequency problem

When two values have the same frequency, the implementation returns the smaller numeric value.

This rule is used in both the naive and efficient implementations so the results are comparable.

## Problem 1 — Duplicate detection

### Algorithm A: Brute force

- Description: compare every pair of values in the array.
- Time complexity: O(n^2)
- Space complexity: O(1)
- Why: for each of n values, the code may compare against up to n - 1 other values.

### Algorithm B: Hash set

- Description: insert each value into a hash set; if a value is already present, a duplicate exists.
- Time complexity: O(n) average case
- Space complexity: O(n)
- Why: each value is inserted and looked up in expected constant time.

### Experimental comparison

1. The efficient implementation is usually faster for large inputs.
2. As input size increases, the brute-force approach grows quadratically.
3. The measured timing should agree with the theoretical prediction.
4. The gap becomes larger because O(n^2) grows much faster than O(n).
5. The faster method uses extra memory for the hash table.

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
- Why: each value may require a full pass through the array.

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
