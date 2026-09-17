CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic -Iinclude -Itests
BUILD_DIR := build
SRC_DIR := src
TEST_DIR := tests
BENCH_DIR := benchmark

ALGO_SRC := $(filter-out $(SRC_DIR)/main.cpp,$(wildcard $(SRC_DIR)/*.cpp))
MAIN_SRC := $(SRC_DIR)/main.cpp
TEST_SRC := $(TEST_DIR)/test_algorithms.cpp
BENCH_SRC := $(BENCH_DIR)/benchmark.cpp

.PHONY: all test benchmark clean

all: $(BUILD_DIR)/main \
     $(BUILD_DIR)/test_algorithms \
     $(BUILD_DIR)/benchmark_app

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main: $(BUILD_DIR) $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) $(MAIN_SRC) -o $@

$(BUILD_DIR)/test_algorithms: $(BUILD_DIR) $(ALGO_SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(ALGO_SRC) $(TEST_SRC) -o $@

$(BUILD_DIR)/benchmark_app: $(BUILD_DIR) $(ALGO_SRC) $(BENCH_SRC)
	$(CXX) $(CXXFLAGS) $(ALGO_SRC) $(BENCH_SRC) -o $@

test: $(BUILD_DIR)/test_algorithms
	./$(BUILD_DIR)/test_algorithms

benchmark: $(BUILD_DIR)/benchmark_app
	./$(BUILD_DIR)/benchmark_app 1000 5

clean:
	rm -rf $(BUILD_DIR)