# Lab 5 — Algorithm Analysis and Performance Comparison

## Course: CS 20 — Advanced Programming with C++

This lab is intentionally small in scope but conceptually deep. Students are given three straightforward algorithmic problems and are asked to implement two correct solutions for each one.

The key idea is simple:

Two correct programs can produce the same answer while having dramatically different performance because of their algorithms.

## Learning objectives

By the end of this lab, students should be able to:

- implement two correct solutions to the same problem;
- identify the Big-O complexity of each solution;
- compare performance using wall-clock timing;
- explain why a more efficient algorithm is faster in practice;
- verify correctness before benchmarking;
- produce and analyze benchmark data in CSV format.

## Problems

### Problem 1 — Find a Duplicate

Given an array of integers, determine whether any value appears more than once.

Implement:

- Solution A: brute force comparison of every pair
- Solution B: hash set membership

Expected complexity:

- Solution A: O(n^2)
- Solution B: O(n) average case

### Problem 2 — Find the Most Frequent Value

Given an array of integers, determine which value occurs most frequently.

Tie-breaking rule:

If two values are tied, return the smaller numeric value.

Implement:

- Solution A: for each value, scan the entire array to count occurrences
- Solution B: hash-based frequency map

Expected complexity:

- Solution A: O(n^2)
- Solution B: O(n) average case

### Problem 3 — Search for Common Elements

Given two arrays, determine how many distinct values appear in both arrays.

Implement:

- Solution A: for every value in the first array, scan the second array
- Solution B: hash-based membership lookup

Expected complexity:

- Solution A: O(n × m)
- Solution B: O(n + m) average case

## Required workflow

For each problem, students must:

1. implement Solution A;
2. implement Solution B;
3. verify both implementations produce the same result;
4. benchmark both with std::chrono::steady_clock;
5. measure several input sizes;
6. compare the results;
7. explain the algorithmic complexity in writing.

## Benchmark design

Students should benchmark on input sizes such as:

- 1,000
- 10,000
- 100,000
- 1,000,000

If the naive algorithm becomes too slow, a smaller maximum test size may be used for that specific experiment. The README should explain why the maximum size was reduced.

The benchmark should measure only the algorithm itself, not data creation, file I/O, or console output.

Use:

- std::chrono::steady_clock
- multiple trials
- median or average timing per input size

Do not include random-data generation or printing inside the timed block.

## Benchmark output format

The benchmark program must print CSV output in this format:

```csv
problem,algorithm,input_size,trial,time_ns
duplicate,naive,1000,1,123456
duplicate,efficient,1000,1,45678
...
```

This makes it easy to plot the results in Python, Excel, or another tool.

## Correctness requirements

Before running performance tests, both implementations for each problem must be validated.

The tests should cover:

- empty arrays where applicable;
- one-element arrays;
- small arrays;
- duplicates and no-duplicate cases;
- negative values;
- repeated values;
- large arrays;
- boundary cases.

The benchmark is not valid if the two algorithms disagree on correctness.

## Repository structure

```text
advanced-cpp-lab005/
├── .github/
│   └── workflows/
│       └── autograde.yml
├── include/
│   ├── common.h
│   ├── duplicate.h
│   ├── frequency.h
│   └── ...
├── src/
│   ├── common.cpp
│   ├── duplicate.cpp
│   ├── frequency.cpp
│   └── ...
├── tests/
│   └── test_algorithms.cpp
├── benchmark/
│   └── benchmark.cpp
├── docs/
│   └── complexity.md
├── README.md
├── CMakeLists.txt
├── Makefile
├── .gitignore
└── ...
```

## GitHub Actions

The provided workflow compiles the project, runs correctness tests, and executes a small benchmark sanity check.

GitHub-hosted runners are not a controlled benchmarking environment, so the full timing experiment should be run locally by students.

## Expected time

This lab should take about 4 to 6 hours and is suitable as an early algorithm-analysis assignment in an advanced C++ course.

## Build and test

```bash
make test
make benchmark
```

The goal is to understand performance, not to create complex problem statements. The assignment is intentionally simple so that students focus on observing the practical effects of algorithmic complexity.
