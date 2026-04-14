# High-Performance CPU Cache Simulator

A trace-driven memory cache simulator written in pure, modern C++. This project benchmarks the efficiency of IBM's Adaptive Replacement Cache (ARC) against a standard Least Recently Used (LRU) baseline.

## ⚙️ Architecture
This system is built as a highly optimized, header-only C++ library.
To achieve $O(1)$ time complexity for all cache operations, the engine bypasses standard arrays and utilizes:
* Custom-built Doubly Linked Lists for instant $O(1)$ eviction.
* `std::unordered_map` for $O(1)$ memory address lookups.
* Four distinct memory routing queues ($T_1, T_2, B_1, B_2$) to handle ARC's dynamic frequency and recency tuning.

## 📊 Benchmarking Results
( will be added once project is completed. ) 
