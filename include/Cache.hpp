#pragma once
#include "CacheLine.hpp"
#include<vector>

struct Cache{
    std::vector<std::vector<CacheLine>> sets; // all sets in a cache 
    uint32_t num_sets;
    uint64_t hits; 
    uint64_t misses;
    uint32_t num_ways;
    uint32_t block_size;
    Cache(uint32_t num_sets, uint32_t num_ways, uint32_t block_size):num_sets(num_sets), num_ways(num_ways), block_size(block_size),
    sets(num_sets, std::vector<CacheLine>(num_ways)), hits(0), misses(0){}
};

void access(Cache& cache, uint64_t address);