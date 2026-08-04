#pragma once
#include "CacheLine.hpp"
#include<vector>

struct Cache{
    std::vector<CacheLine> sets; // all sets in a cache 
    uint32_t num_sets;
    uint32_t hits; 
    uint32_t misses;
    Cache():num_sets(64), sets(64), hits(0), misses(0){}
};

void access(Cache& cache, uint32_t address);