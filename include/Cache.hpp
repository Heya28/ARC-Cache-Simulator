#pragma once
#include "CacheLine.hpp"
#include<vector>

struct Cache{
    std::vector<std::vector<CacheLine>> sets; // all sets in a cache 
    uint32_t num_sets;
    uint32_t hits; 
    uint32_t misses;
    uint32_t num_ways;
    Cache(uint32_t num_sets, uint32_t num_ways):num_sets(num_sets), num_ways(num_ways), 
    sets(num_sets, std::vector<CacheLine>(num_ways)), hits(0), misses(0){}
};

void access(Cache& cache, uint32_t address);