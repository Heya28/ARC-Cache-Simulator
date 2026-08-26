# CPU Cache Simulator

A trace-driven CPU cache simulator built in C++ for analyzing memory
access patterns, cache behavior, replacement policies and miss types.

## Implemented

- **Address decoding** — Tag, index and offset extraction for
  power-of-two cache configurations.
- **N-way set-associative cache** — Supports N-way set associativity,
  with direct-mapped caching represented by the N=1 case.
- **True LRU replacement** — Tracks and applies least-recently-used
  replacement within each cache set.
- **Miss Classification Engine** — Classifies cache misses as
  **Compulsory, Capacity, or Conflict** using a three-cache reference
  model:
  - Infinite fully-associative cache for compulsory misses.
  - Same-capacity fully-associative cache for capacity misses.
  - Real cache configuration for conflict misses.

## In Progress

- **Miss-classification test suite** — Adding traces specifically
  designed to exercise and validate capacity and conflict misses.
- **Adaptive Replacement Cache (ARC)** policy.

## Build

\`\`\`bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/AddressDecoder.cpp src/Cache.cpp src/MissClassifier.cpp src/main.cpp -o cache_sim
\`\`\`

## Run

\`\`\`bash
./cache_sim
\`\`\`