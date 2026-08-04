# CPU Cache Simulator

A trace-driven cache simulator built in C++.

## Currently implemented
- Direct-mapped cache with hit/miss tracking

## In progress
- N-way set-associative cache with LRU replacement
- ARC (Adaptive Replacement Cache)

## Build
```bash
g++ -I include src/AddressDecoder.cpp src/Cache.cpp src/main.cpp -o cache_sim
```

## Run
```bash
./cache_sim
```